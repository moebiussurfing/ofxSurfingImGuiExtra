/*==============================================================================
    ImGuiExtension : NodeCanvas

    Copyright (c) 2020 Daan de Lange - http://daandelange.com/

    Mosaic is distributed under the MIT License. This gives everyone the
    freedoms to use Mosaic in any context: commercial or non-commercial,
    public or private, open or closed source.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    DESCRIPTION
    This is an ImGui extension that allows drawing nodes on a canvas.
    No node engine nor logic is included; this is pure GUI stuff.

    INFO
    If you edit this file, I recommend working with the ImGui inspector ImGui::ShowMetricsWindow().
    Everything is vanilla ImGui using only core API calls.

    Tested with IMGUI 1.75 WIP
    https://github.com/ocornut/imgui/
    Inspired by several other node projects mentioned in https://github.com/ocornut/imgui/issues/306

    Made for Mocaic, but could be of use in any other project.
    https://mosaic.d3cod3.org/
==============================================================================*/

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_node_canvas.h"
#include <type_traits>
#include <bitset> // bitset::count
#include <algorithm>

// NodePin Connection types in ImGui namespace
#define IMGUI_PAYLOAD_TITLE_INLET        "INLET_"  //
#define IMGUI_PAYLOAD_TITLE_OUTLET       "OUTLET_" //

// ImGui helper func
static inline ImVec2 ImAbs(const ImVec2& lhs) {
    return ImVec2(lhs.x > 0.0f ? lhs.x : std::abs(lhs.x), lhs.y > 0.0f ? lhs.y : std::abs(lhs.y));
}

inline ImVec2 eval_bezier(float t, const ImGuiEx::BezierCurve& bezier){
    // B(t) = (1-t)**3 p0 + 3(1 - t)**2 t P1 + 3(1-t)t**2 P2 + t**3 P3
    return ImVec2(
                (1 - t) * (1 - t) * (1 - t) * bezier.p0.x +
                3 * (1 - t) * (1 - t) * t * bezier.p1.x +
                3 * (1 - t) * t * t * bezier.p2.x + t * t * t * bezier.p3.x,
                (1 - t) * (1 - t) * (1 - t) * bezier.p0.y +
                3 * (1 - t) * (1 - t) * t * bezier.p1.y +
                3 * (1 - t) * t * t * bezier.p2.y + t * t * t * bezier.p3.y);
}

// Divides the bezier curve into n segments. Evaluates the distance to each
// segment. Chooses the segment with the smallest distance, and repeats the
// algorithm on that segment, for the given number of iterations.
inline float get_closest_point_on_cubic_bezier(const int num_iterations, const int num_segments, const ImVec2& pos, const ImGuiEx::BezierCurve& bezier){
    assert(num_iterations > 0 && num_segments > 0);
    float tstart = 0.0f;
    float tend = 1.0f;
    float tbest = 0.5f;
    float best_distance = FLT_MAX;

    for (int i = 0; i < num_iterations; ++i) {
        // split the current t-range to segments
        const float dt = (tend - tstart) / num_segments;
        for (int s = 0; s < num_segments; ++s) {
            const float tmid = tstart + dt * (float(s) + 0.5f);
            const ImVec2 bt = eval_bezier(tmid, bezier);
            const ImVec2 dv = bt - pos;
            float cur_distance = ImLengthSqr(dv);
            if (cur_distance < best_distance) {
                best_distance = cur_distance;
                tbest = tmid;
            }
        }
        // shrink the current t-range to the best segment
        tstart = tbest - 0.5f * dt;
        tend = tbest + 0.5f * dt;
    }

    return tbest;
}

inline float get_distance_to_cubic_bezier(const ImVec2& pos, const ImGuiEx::BezierCurve& bezier){
    const int segments = 5;
    const float length = ImSqrt(ImLengthSqr(bezier.p3 - bezier.p2)) +
            ImSqrt(ImLengthSqr(bezier.p2 - bezier.p1)) +
            ImSqrt(ImLengthSqr(bezier.p1 - bezier.p0));
    const float iterations_per_length = 0.01f;
    const int iterations =
            int(ImClamp(length * iterations_per_length, 2.0f, 8.f));

    const float t =
            get_closest_point_on_cubic_bezier(iterations, segments, pos, bezier);
    const ImVec2 point_on_curve = eval_bezier(t, bezier);

    const ImVec2 to_curve = point_on_curve - pos;
    return ImSqrt(ImLengthSqr(to_curve));
}

inline ImRect get_containing_rect_for_bezier_curve(const ImGuiEx::BezierCurve& bezier){
    const ImVec2 min = ImVec2(
                ImMin(bezier.p0.x, bezier.p3.x), ImMin(bezier.p0.y, bezier.p3.y));
    const ImVec2 max = ImVec2(
                ImMax(bezier.p0.x, bezier.p3.x), ImMax(bezier.p0.y, bezier.p3.y));

    ImRect rect(min, max);
    rect.Add(bezier.p1);
    rect.Add(bezier.p2);

    return rect;
}

inline ImGuiEx::LinkBezierData get_link_renderable(ImVec2 start, ImVec2 end, const float line_segments_per_length){

    // function arguments assed by value, since we mutate them
    const ImVec2 delta = end - start;
    const float link_length = ImSqrt(ImLengthSqr(delta));
    const ImVec2 offset = ImVec2(0.25f * link_length, 0.f);
    ImGuiEx::LinkBezierData link_data;
    link_data.bezier.p0 = start;
    link_data.bezier.p1 = start + offset;
    link_data.bezier.p2 = end - offset;
    link_data.bezier.p3 = end;
    link_data.num_segments = ImMax(int(link_length * line_segments_per_length), 1);
    return link_data;
}

inline bool is_mouse_hovering_near_link(const ImGuiEx::BezierCurve& bezier){
    const ImVec2 mouse_pos = ImGui::GetIO().MousePos;

    // First, do a simple bounding box test against the box containing the link
    // to see whether calculating the distance to the link is worth doing.
    const ImRect link_rect = get_containing_rect_for_bezier_curve(bezier);

    if (link_rect.Contains(mouse_pos))
    {
        const float distance = get_distance_to_cubic_bezier(mouse_pos, bezier);
        if (distance < IMGUI_EX_NODE_HOVER_DISTANCE)
        {
            return true;
        }
    }

    return false;
}


bool ImGuiEx::NodeCanvas::Begin(const char* _id){

    // Verify orchestration of ImGui function calls
    IM_ASSERT(isDrawingCanvas == false); // Always call End(), even when Begin() returns true.
    IM_ASSERT(isDrawingNode == false); // forgot to EndNode()
    IM_ASSERT(canDrawNode == false); // forgot to End()

    // Spawn container window
    // You can set pos and size like any imgui window ( ImGui::setNextWindowPos )
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0)); // full frame
    bool ret = ImGui::Begin(_id, NULL,
                            ImGuiWindowFlags_NoMove |
                            ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoBackground |
                            ImGuiWindowFlags_NoDecoration |
                            ImGuiWindowFlags_NoNavFocus |
                            ImGuiWindowFlags_NoNav |
                            ImGuiWindowFlags_NoBringToFrontOnFocus |
                            ImGuiWindowFlags_NoScrollWithMouse |
                            ImGuiWindowFlags_NoScrollbar |
                            ImGuiWindowFlags_NoMouseInputs
                            );
    ImGui::PopStyleVar();

    // Allow tinier windows for nodes.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(IMGUI_EX_NODE_MIN_WIDTH, IMGUI_EX_NODE_MIN_HEIGHT) );

    // Store a common canvas draw buffer.
    canvasDrawList = ImGui::GetWindowDrawList();

    // todo : return early when invisible ? (Can this window be invisible ?)

    // Never focus to this window ?
    //ImGui::SetWindowFocus(false);

    // Not needed but could be later if ImGui takes over canvas scrolling.
    // Emit dummy widget matching bounds of the canvas to the window know the content size
    //    ImGui::SetCursorScreenPos(canvasView.viewRect.Min);
    //    ImGui::Dummy(canvasView.contentRect.GetSize());

    canDrawNode = ret;
    isDrawingCanvas = true;
    isDrawingNode = false;
    return ret;
}

void ImGuiEx::NodeCanvas::End(){
    // check calls
    IM_ASSERT(isDrawingCanvas == true); // // Begin() wasn't called
    IM_ASSERT(isDrawingNode == false); // Forgot to call EndNode()

    isAnyCanvasNodeHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);

    // Got links (selection) to delete ?
//    if( ImGui::GetIO().KeysDown[ImGui::GetIO().KeyMap[ImGuiKey_Delete]] && selectedLinks.size()>0 && !ImGui::IsAnyItemFocused() ){
//        selectedLinksToDelete = selectedLinks;
//        selectedLinks.resize(0);
//        //std::cout << "Delete pressed, preparing for deletion." << std::endl;
//    }

    // reset cursor pos to canvas window
    ImGui::SetCursorPos(ImGui::GetWindowContentRegionMin());

# if __IMGUI_EX_NODECANVAS_DEBUG__
    // Visualise Canvas Window size
    ImGui::GetForegroundDrawList()->AddRect(ImGui::GetWindowContentRegionMin(), ImGui::GetWindowContentRegionMax(), IM_COL32(255,255,0,255));
# endif

    // Close Canvas window
    ImGui::PopStyleVar(); // restore min win size
    ImGui::End();

    // Update state
    isDrawingCanvas = false;
    canDrawNode = false;
    canvasDrawList = nullptr;
}

void ImGuiEx::NodeCanvas::DrawFrameBorder(const bool& _drawOnForeground) const {
    // Only use between NodeCanvas::Begin() and End().
    IM_ASSERT(isDrawingCanvas == true);  // forgot to Begin();
    IM_ASSERT(canDrawNode == true); // Don't call when Begin() returned true !
    IM_ASSERT(isDrawingNode == false); // Don't call within BeginNode() !

    // visualise viewport with a small offset
    ImDrawList* layer = _drawOnForeground ? ImGui::GetForegroundDrawList() : canvasDrawList ;
    layer->AddRect(
                ImGui::GetCurrentWindow()->Rect().Min +ImGui::GetStyle().WindowPadding,
                ImGui::GetCurrentWindow()->Rect().Max-ImGui::GetStyle().WindowPadding,
                //IM_COL32(255, 255, 255, 64)
                ImGui::GetColorU32( ImGuiCol_HeaderActive )
                );
}


// always use EndNode() even if returns false. Like ImGui Windows.
bool ImGuiEx::NodeCanvas::BeginNode( const char* _id, std::string _name, ImVec2& _pos, ImVec2& _size, const int& _numLeftPins, const int& _numRightPins, const bool& _canResize, const bool& _reduceNodeFrame ){
    // Check callstack
    IM_ASSERT(isDrawingCanvas == true);  // forgot to End();
    IM_ASSERT(canDrawNode == true); // Don't call if Begin() returned false
    IM_ASSERT(isDrawingNode == false); // Finish your previous node before staring a new one !

    // Precalc some vars, valid until EndNode() is called
    ImVec2 nodeScale = ImVec2(1,1)*canvasView.scale;
    curNodeData = NodeLayoutData(canvasView.translation + _pos*nodeScale, _size*nodeScale, canvasView.scale );
    isDrawingNode = true; // to allow End() call
    curNodeData.menuActions = ImGuiExNodeMenuActionFlags_None; // reset menu flags

    // Is the node out of sight on canvas ?
    bool isNodeVisible = ImGui::IsRectVisible( curNodeData.outerContentBox.Min, curNodeData.outerContentBox.Max );
    if( !isNodeVisible ){
        curNodeData.zoomName = ImGuiExNodeZoom_Invisible;
        return false; // Todo: don't return early so pin locations update when the emitting box is invisible.
    }

    // Calc zoom name
    {
        unsigned int curWidth = curNodeData.outerContentBox.GetSize().x;
        if( curWidth < IMGUI_EX_NODE_MIN_WIDTH_SMALL )
            curNodeData.zoomName = ImGuiExNodeZoom_Imploded;
        else if( curWidth < IMGUI_EX_NODE_MIN_WIDTH_NORMAL )
            curNodeData.zoomName = ImGuiExNodeZoom_Small;
        else if( curWidth < IMGUI_EX_NODE_MIN_WIDTH_LARGE )
            curNodeData.zoomName = ImGuiExNodeZoom_Normal;
        else
            curNodeData.zoomName = ImGuiExNodeZoom_Large;
    }
    //curNodeData.viewName = ImGuiExNodeView_None;

    // Adapt the pin space to the layout
    // Backup, to set various pin sizes depending on the zoom level
    int pinsWidth = 0;
//    if(curNodeData.zoomName == ImGuiExNodeZoom_Imploded){
//        // Behaviour: if there are any pins, show only pins. Else imploded still have small content.
//        pinsWidth = 0;
// //        if(_numLeftPins > 0 || _numLeftPins > 0)
// //            pinsWidth = ImFloor(curNodeData.innerContentBox.GetSize().x);
// //        if(_numLeftPins > 0 && _numLeftPins > 0)
// //            pinsWidth *= .5f;
//    }
//    else{
//        //pinsWidth = (curNodeData.zoomName >= ImGuiExNodeZoom_Large) ? IMGUI_EX_NODE_PINS_WIDTH_LARGE : (curNodeData.zoomName >= ImGuiExNodeZoom_Normal) ? IMGUI_EX_NODE_PINS_WIDTH_NORMAL : IMGUI_EX_NODE_PINS_WIDTH_SMALL;
//        pinsWidth = (curNodeData.zoomName >= ImGuiExNodeZoom_Large) ? IMGUI_EX_NODE_PINS_WIDTH_LARGE : (curNodeData.zoomName >= ImGuiExNodeZoom_Normal) ? IMGUI_EX_NODE_PINS_WIDTH_NORMAL : IMGUI_EX_NODE_PINS_WIDTH_SMALL;
//    }

    // Remove pins space from innerContentBox if there are any pins
    if( _numLeftPins > 0 ){ // Has left pins
        pinsWidth = IMGUI_EX_NODE_PINS_WIDTH_NORMAL;
        curNodeData.pinsFlags |= ImGuiExNodePinsFlags_Left;
        curNodeData.leftPins.region.Max.x += pinsWidth;
        curNodeData.innerContentBox.Min.x += pinsWidth;

        curNodeData.leftPins.numPins = _numLeftPins;
        curNodeData.leftPins.pinSpace = ImVec2(curNodeData.leftPins.region.GetSize().x, curNodeData.leftPins.region.GetSize().y / _numLeftPins);
        curNodeData.leftPins.curDrawPos = curNodeData.leftPins.region.Min;
    }
    if( _numRightPins > 0 ){ // Has right pins
        pinsWidth = IMGUI_EX_NODE_PINS_WIDTH_SMALL;
        curNodeData.pinsFlags |= ImGuiExNodePinsFlags_Right;
        curNodeData.rightPins.region.Min.x -= pinsWidth;
        curNodeData.innerContentBox.Max.x -= pinsWidth;

        curNodeData.rightPins.numPins = _numRightPins;
        curNodeData.rightPins.pinSpace = ImVec2(curNodeData.rightPins.region.GetSize().x, curNodeData.rightPins.region.GetSize().y / _numRightPins);
        curNodeData.rightPins.curDrawPos = ImVec2(curNodeData.rightPins.region.Max.x, curNodeData.rightPins.region.Min.y);
    }

#if __IMGUI_EX_NODECANVAS_DEBUG__
    // For debugging, draw all parts of the node
    ImDrawList* fg = ImGui::GetForegroundDrawList();
    fg->AddRect(curNodeData.rightPins.region.Min, curNodeData.rightPins.region.Max, IM_COL32(255,255,255,200));
    fg->AddRect(curNodeData.leftPins.region.Min, curNodeData.leftPins.region.Max, IM_COL32(255,255,255,200));
    fg->AddRect(curNodeData.innerContentBox.Min, curNodeData.innerContentBox.Max, IM_COL32(255,255,255,200));
    //fg->AddRect(curNodeData.innerContentBox.Min, curNodeData.innerContentBox.Max, IM_COL32(255,255,255,200));
    fg->AddRect(curNodeData.outerContentBox.Min, curNodeData.outerContentBox.Max, IM_COL32(255,255,255,200));
    fg->AddRect(curNodeData.outerContentBox.Min, ImVec2(curNodeData.outerContentBox.Max.x,curNodeData.outerContentBox.Min.y+IMGUI_EX_NODE_HEADER_HEIGHT), IM_COL32(255,255,255,200));
    fg->AddRect(ImVec2(curNodeData.outerContentBox.Min.x, curNodeData.outerContentBox.Max.y-IMGUI_EX_NODE_FOOTER_HEIGHT), curNodeData.outerContentBox.Max, IM_COL32(255,255,255,200));
#endif

    // Create node window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));//IMGUI_EX_NODE_CONTENT_PADDING,IMGUI_EX_NODE_CONTENT_PADDING));
    ImGui::SetNextWindowPos(curNodeData.outerContentBox.Min);
    ImGui::SetNextWindowSize(curNodeData.outerContentBox.GetSize());
    //ImGui::SetNextWindowSize(ImVec2(curNodeData.outerContentBox.GetSize().x,0.0f));
    bool ret = ImGui::Begin(_id, NULL,
                            ImGuiWindowFlags_NoMove
                            | ImGuiWindowFlags_NoBackground
                            | ImGuiWindowFlags_NoDecoration
                            //| ImGuiWindowFlags_AlwaysAutoResize
                            //| ImGuiWindowFlags_AlwaysUseWindowPadding
                            | ImGuiWindowFlags_NoFocusOnAppearing
                            );
    // Save draw context
    nodeDrawList = ImGui::GetWindowDrawList();
    bool nodeMenuIsOpen = false;

    ImGui::PopStyleVar(1);

    // Node namespace
    ImGui::PushID(_id);

    // Add clipping Area to mask outer-node space. (wires will have to be drawn somewhere else)
    ImGui::PushClipRect( curNodeData.outerContentBox.Min, curNodeData.outerContentBox.Max, true);

    // Draw Outer region
    {
        // Node BG fill
        if(curNodeData.zoomName < ImGuiExNodeZoom_Small || !_reduceNodeFrame){
            // Dont care about the pin space in small zoom levels
            nodeDrawList->AddRectFilled( curNodeData.outerContentBox.Min, curNodeData.outerContentBox.Max, ImGui::GetColorU32(ImGuiCol_FrameBg, 999.f));
        }else{
            // Whole content zone = transparent.
            nodeDrawList->AddRectFilled( curNodeData.outerContentBox.Min, curNodeData.outerContentBox.Max, IM_COL32(0,0,0,0));
            // Left pins BG
            nodeDrawList->AddRectFilled( curNodeData.outerContentBox.Min, ImVec2(curNodeData.outerContentBox.Min.x+curNodeData.leftPins.region.GetSize().x,curNodeData.outerContentBox.Max.y), ImGui::GetColorU32(ImGuiCol_FrameBg, 999.f));
            // Right pins BG
            nodeDrawList->AddRectFilled( curNodeData.rightPins.region.Min, curNodeData.outerContentBox.Max, ImGui::GetColorU32(ImGuiCol_FrameBg, 999.f));
        }

        // Draw HeaderBar BG
        nodeDrawList->AddRectFilled(
                    curNodeData.outerContentBox.Min,
                    curNodeData.outerContentBox.Min+ImVec2(curNodeData.outerContentBox.GetSize().x, IMGUI_EX_NODE_HEADER_HEIGHT),
                    ImGui::GetColorU32(ImGuiCol_Header)
                    );

        // Draw footer
        nodeDrawList->AddRectFilled(
                    ImVec2(curNodeData.outerContentBox.Min.x, curNodeData.outerContentBox.Max.y-IMGUI_EX_NODE_FOOTER_HEIGHT),
                    curNodeData.outerContentBox.Max,
                    ImGui::GetColorU32(ImGuiCol_Header)
                    );

        // Node border (surrounding)
        nodeDrawList->AddRect( curNodeData.outerContentBox.Min+ImVec2(1,1), curNodeData.outerContentBox.Max-ImVec2(1,1), ImGui::GetColorU32(ImGuiCol_Border) );

        // Header info
        ImGui::SetCursorScreenPos( curNodeData.outerContentBox.Min+ImVec2(5, (IMGUI_EX_NODE_HEADER_HEIGHT-ImGui::CalcTextSize("").y)*.5f) );//canvasView.translation+pos+ImVec2(5,4));
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,255,255,255));
        ImGui::Text("%s", _name.c_str()); // title
        ImGui::PopStyleColor();

        // Enable drag on title
        //unsigned int curTabsWidth = (curNodeData.zoomName > ImGuiExNodeZoom_Imploded) ? IMGUI_EX_NODE_HEADER_TOOLBAR_WIDTH : 0;
        ImGui::SetCursorScreenPos( curNodeData.outerContentBox.Min );
        //ImGui::InvisibleButton( "headerGripBtn", ImVec2( curNodeData.outerContentBox.GetSize().x-curTabsWidth, IMGUI_EX_NODE_HEADER_HEIGHT )  );
        {
            // InvisibleButton() cannot have 0 size arg !
            ImVec2 tmpSize( curNodeData.outerContentBox.GetSize().x-IMGUI_EX_NODE_HEADER_HEIGHT, IMGUI_EX_NODE_HEADER_HEIGHT );
            if(tmpSize.x==0) tmpSize.x=0.1f;
            if(tmpSize.y==0) tmpSize.y=0.1f;
            ImGui::InvisibleButton( "headerGripBtn", tmpSize );

        }
        static ImVec2 mouseOffset(0,0);
        static bool isDraggingHeader = false;

        if(ImGui::IsItemActive() && ImGui::IsMouseDragging(0)){
            if(!isDraggingHeader){
                mouseOffset = ImGui::GetMousePos()-curNodeData.outerContentBox.Min;
                isDraggingHeader = true;
            }

# if __IMGUI_EX_NODECANVAS_DEBUG__
            // Visualise mouse offset
            ImGui::GetForegroundDrawList()->AddLine(curNodeData.outerContentBox.Min,curNodeData.outerContentBox.Min+mouseOffset,ImGui::ColorConvertFloat4ToU32(ImVec4(0,1,0,1.f)));
# endif
            _pos = (ImGui::GetMousePos()-mouseOffset)*(1.f/canvasView.scale)-canvasView.translation*(1.f/canvasView.scale);// ImGui::GetMouseDragDelta(0);
        }
        else if(ImGui::IsItemDeactivated()){
            if(isDraggingHeader) isDraggingHeader = false;
        }

        // Tab bar and widget info
        if( curNodeData.zoomName > ImGuiExNodeZoom_Imploded ){

            // Tabs
            /*ImGui::SetCursorScreenPos(ImVec2(curNodeData.outerContentBox.Max.x-IMGUI_EX_NODE_HEADER_TOOLBAR_WIDTH, curNodeData.outerContentBox.Min.y + 2));
            if(ImGui::BeginTabBar("widgetTabs",ImGuiTabBarFlags_NoTooltip)){//, ImGuiTabBarFlags_FittingPolicyResizeDown)){

                static bool tabInfoOpen = true, tabVisualiseOpen = false, tabParamsOpen = false;
                ImGui::SetCursorScreenPos(ImVec2(curNodeData.outerContentBox.Max.x-IMGUI_EX_NODE_HEADER_TOOLBAR_WIDTH, ImGui::GetCursorScreenPos().y));
                ImGui::SameLine();
                //if(ImGui::BeginTabItem("i", &tabInfoOpen, ImGuiTabItemFlags_NoCloseButton | ImGuiTabItemFlags_NoCloseWithMiddleMouseButton )) ImGui::EndTabItem();
                if((tabVisualiseOpen = ImGui::BeginTabItem("v",NULL, ImGuiTabItemFlags_NoCloseButton)))ImGui::EndTabItem();
                if((tabParamsOpen = ImGui::BeginTabItem("p",NULL, ImGuiTabItemFlags_NoCloseButton)))ImGui::EndTabItem();
                if((tabInfoOpen = ImGui::BeginTabItem("i",NULL, ImGuiTabItemFlags_NoCloseButton))) ImGui::EndTabItem();

                // Set view state
                curNodeData.viewName = tabInfoOpen ? ImGuiExNodeView_Info : tabVisualiseOpen ? ImGuiExNodeView_Visualise : tabParamsOpen ? ImGuiExNodeView_Params : ImGuiExNodeView_None;

                // Node Menu Toggle
                ImGui::SameLine();
                ImGui::Button("#");
                if(ImGui::IsItemActivated()){
                    nodeMenuIsOpen = true;
                }

                ImGui::EndTabBar();

                // draw line over tab bar to fit 100% width
                nodeDrawList->AddLine(
                            curNodeData.outerContentBox.Min+ImVec2(0,IMGUI_EX_NODE_HEADER_HEIGHT - 1),
                            ImVec2( curNodeData.outerContentBox.Max.x, curNodeData.outerContentBox.Min.y + IMGUI_EX_NODE_HEADER_HEIGHT - 1),
                            ImGui::GetColorU32(ImGuiCol_WindowBg)
                            );
            }*/

            // NO TABS DESIGN -- TESTING

            // Node Menu Toggle
            ImGui::SetCursorScreenPos(ImVec2(curNodeData.outerContentBox.Max.x-18, curNodeData.outerContentBox.Min.y + 1));
            ImGui::Button("#");
            if(ImGui::IsItemActivated()){
                nodeMenuIsOpen = true;
            }

            curNodeData.viewName = ImGuiExNodeView_Visualise;
        }

        // Draw footer resize handle
        if(_canResize){
            ImGui::SetCursorScreenPos( curNodeData.outerContentBox.Max-ImVec2( IMGUI_EX_NODE_FOOTER_HANDLE_SIZE, IMGUI_EX_NODE_FOOTER_HANDLE_SIZE )  );
            ImGui::InvisibleButton( "footerGripBtn", ImVec2( IMGUI_EX_NODE_FOOTER_HANDLE_SIZE, IMGUI_EX_NODE_FOOTER_HANDLE_SIZE )  );
            static bool isDraggingFooter = false;
            if(ImGui::IsItemActive() && ImGui::IsMouseDragging(0)){
                if(!isDraggingFooter){
                    isDraggingFooter=true;
                }
                // Constrained size
                _size = ImMax(
                            (ImGui::GetMousePos()-curNodeData.outerContentBox.Min)*(1.f/canvasView.scale),
                            ImVec2(IMGUI_EX_NODE_MIN_WIDTH,IMGUI_EX_NODE_MIN_HEIGHT)
                            );
            }
            else if(ImGui::IsItemDeactivated()){
                if(isDraggingFooter) isDraggingFooter = false;
            }

            // Triangle grip
            nodeDrawList->AddTriangleFilled(
                        curNodeData.outerContentBox.Max-ImVec2( 0, IMGUI_EX_NODE_FOOTER_HEIGHT*2 ),
                        curNodeData.outerContentBox.Max,
                        curNodeData.outerContentBox.Max-ImVec2( IMGUI_EX_NODE_FOOTER_HEIGHT*2, 0 ),
                        //ImGui::GetColorU32(ImGuiCol_ResizeGrip)
                        ImGui::GetColorU32(ImGui::IsItemActive()?ImGuiCol_ResizeGripActive:ImGui::IsItemHovered()?ImGuiCol_ResizeGripHovered:ImGuiCol_ResizeGrip )
                        );
        }

    }

    // Return before drawing content, if scale is too small ?
    // todo. (This is already partially handled by BeginNodeContent();)
    if( false && curNodeData.zoomName < ImGuiExNodeZoom_Small ){
        // Fill empty space with color
        //canvasDrawList->AddRectFilled(); // todo

        // Todo: something with : window->SkipItems to prevent drawing to node ?
        return false;
    }

    // reset origin
    ImGui::SetCursorScreenPos( curNodeData.innerContentBox.Min );

    // The combination of a cliprect and columns allows us to set a clipping space for node widgets while reserving drawable space for pins, without having to add an extra window / childframe.
    ImGui::PushClipRect( curNodeData.leftPins.region.Min, curNodeData.rightPins.region.Max, true); // Inner space + Node Spaces
    ImGui::BeginColumns("innerNode", 3,
                        ImGuiColumnsFlags_NoBorder
                        | ImGuiColumnsFlags_NoResize
                        //| ImGuiColumnsFlags_NoPreserveWidths
                        | ImGuiColumnsFlags_NoForceWithinWindow // important so there's no weird auto adjustments.
                        );
    // Column layout
    ImGui::SetColumnOffset(0,0);
    ImGui::SetColumnOffset(1,curNodeData.leftPins.region.GetSize().x);
    ImGui::SetColumnOffset(2,curNodeData.innerContentBox.Max.x-curNodeData.leftPins.region.Min.x);

    // move to middle column where the user can draw
    ImGui::NextColumn();

    // Draw column BG, to mask overlapping nodes
    /*if( curNodeData.zoomName > ImGuiExNodeZoom_Imploded ){
        ImGui::GetWindowDrawList()->AddRectFilled(curNodeData.innerContentBox.Min, curNodeData.innerContentBox.Max, ImGui::GetColorU32(ImGuiCol_FrameBg, 999.f) );
        ImGui::Dummy(ImVec2(-1,IMGUI_EX_NODE_CONTENT_PADDING));// Padding top
    }*/

    // By default, try to draw full width
    //ImGui::PushItemWidth(-1.0f); // Todo: doesn't seem have any effect...

    // Allow User to catch the menu and extend it
    if( nodeMenuIsOpen ){
        ImGui::OpenPopup(IMGUI_EX_NODE_MENU_ID);
    }

    // Draw default menu items
    if(ImGui::BeginPopup(IMGUI_EX_NODE_MENU_ID)){
        if(_name != "audio device"){ // todo: This cannot be hardcoded in here...
            if(ImGui::MenuItem("Delete")) curNodeData.menuActions |= ImGuiExNodeMenuActionFlags_DeleteNode;
            //if(ImGui::MenuItem("Copy")) curNodeData.menuActions |= ImGuiExNodeMenuActionFlags_CopyNode;
            if(ImGui::MenuItem("Duplicate")) curNodeData.menuActions |= ImGuiExNodeMenuActionFlags_DuplicateNode;
        }
        ImGui::EndPopup();
    }

    return ret;
}

void ImGuiEx::NodeCanvas::EndNode() {
    // Verify ImGui call stack
    IM_ASSERT(isDrawingCanvas == true); // Call ImGuiEx::NodeCanvas::Begin() first !
    IM_ASSERT(isDrawingNode == true); // Call ImGuiEx::NodeCanvas::BeginNode() first !
    IM_ASSERT(isDrawingMenu == false); // You didn't finish your menu ! EndNodeMenu()
    IM_ASSERT(isDrawingContent == false); // Check EndNodeContent(); calls

    if(curNodeData.zoomName > ImGuiExNodeZoom_Invisible ){

        // Only pop these if content is drawn
        /*if( true || curNodeData.zoomName > ImGuiExNodeZoom_Imploded ){
            //ImGui::PopItemWidth();
            ImGui::Dummy(ImVec2(-1,IMGUI_EX_NODE_CONTENT_PADDING)); // Padding bottom
            ImGui::EndColumns();
            ImGui::PopClipRect(); // Inner space + nodes
        }

        // Always pop these ()
        ImGui::PopClipRect();*/

        //ImGui::EndGroup();
        ImGui::PopID();
        ImGui::End();

    }

    // manage state
    isDrawingNode = false;
    nodeDrawList = nullptr;
}

void ImGuiEx::NodeCanvas::SetTransform(const ImVec2& _origin, float _scale){
    // Verify orchestration of ImGui function calls
    IM_ASSERT(isDrawingCanvas == false); // Please set the view before NodeCanvas::Begin()

    canvasView.setTransform( _origin, _scale );
}

// Pin functions
//void ImGuiEx::NodeCanvas::BeginNodePins(  const int& _numPins, const ImGuiExNodePinsFlags& _pinFlags ){
//    // Check ImGui Callstack
//    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
//    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
//    //IM_ASSERT(isDrawingPin == false); // Forgot to call EndNodePins() ?

//    // Modify layout and init draw data
//    int pinsWidth = IMGUI_EX_NODE_PINS_WIDTH_SMALL; // todo: adapt to layout here
//    if( _pinFlags==ImGuiExNodePinsFlags_Left ){
//        curNodeData.leftPins.region.Max.x += pinsWidth;
//        curNodeData.innerContentBox.Min.x += pinsWidth;

//        curNodeData.leftPins.numPins = _numPins;
//        curNodeData.leftPins.pinSpace = (curNodeData.leftPins.region.GetSize() / ImVec2(_numPins, _numPins));
//        curNodeData.leftPins.curDrawPos = curNodeData.leftPins.region.Min;
//    }
//    else if( _pinFlags==ImGuiExNodePinsFlags_Right ){
//        curNodeData.rightPins.region.Min.x -= pinsWidth;
//        curNodeData.innerContentBox.Max.x -= pinsWidth;

//        curNodeData.rightPins.numPins = _numPins;
//        curNodeData.rightPins.pinSpace = (curNodeData.rightPins.region.GetSize() / ImVec2(_numPins, _numPins));
//        curNodeData.rightPins.curDrawPos = curNodeData.rightPins.region.Min;
//    }

//    // todo
//    // Push clip rect to endure not to draw over content

//    // Set pins draw state
//    //curPinsNum = _numPins;
//    //isDrawingPin = true;
//    //curPinFlags = _pinFlags;
//}
//void ImGuiEx::NodeCanvas::EndNodePins(){
//    // Check ImGui Callstack
//    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
//    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
//    //IM_ASSERT(isDrawingPin == true); // Forgot to call BeginNodePins() ?

//    // Set pins state
//    //curPinsNum = 0;
//    //isDrawingPin = false;
//    //curPinFlags = ImGuiExNodePinsFlags_Left; // resets
//}

// Original method by @d3cod3, to remove later ?
ImGuiEx::NodeConnectData ImGuiEx::NodeCanvas::AddNodePin( const int nodeID, const int pinID, const char* _label, ImVec2& _pinPosition, std::vector<ofxVPLinkData>& _linksData, std::string _type, bool _connected, const ImU32& _color, const ImGuiExNodePinsFlags& _pinFlag ){
/*
    ImGuiEx::NodeConnectData connectData;
    connectData.connectType = -1;
    connectData.linkID = -1;
    connectData.fromObjectID = -1;
    connectData.fromOutletPinID = -1;
    connectData.toObjectID = -1;
    connectData.toInletPinID = -1;

    static int connectType = 0;
    static int fromObjectID = 0;
    static int outletPinID = 0;
    static int linkID = -1;

    // Check ImGui Callstack
    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
    IM_ASSERT(_pinFlag == ImGuiExNodePinsFlags_Left || _pinFlag == ImGuiExNodePinsFlags_Right); // Only left / right pins can be created
    IM_ASSERT(curNodeData.pinsFlags & _pinFlag); // Node was not created with correct flags

    // Choose a side
    PinLayout& pinLayout = (_pinFlag==ImGuiExNodePinsFlags_Left) ? curNodeData.leftPins : curNodeData.rightPins;
    // Backup cursor
    ImVec2 cursorBackup = ImGui::GetCursorScreenPos();

    // Move to column
    ImGui::NextColumn(); // right col
    if( _pinFlag==ImGuiExNodePinsFlags_Left ) ImGui::NextColumn(); // left column

    // Hover interaction
    if(pinLayout.pinSpace.x > 0){
        if( _pinFlag==ImGuiExNodePinsFlags_Left ){
            ImGui::SetCursorScreenPos( pinLayout.curDrawPos  );
        }
        else {
            ImGui::SetCursorScreenPos( pinLayout.curDrawPos + ImVec2( -pinLayout.pinSpace.x, 0)  );
        }


# if __IMGUI_EX_NODECANVAS_DEBUG__
        ImGui::Button("##nodeBtn", pinLayout.pinSpace);
# else
        ImGui::InvisibleButton("nodeBtn", ImMax(ImVec2(pinLayout.pinSpace.x,pinLayout.pinSpace.y*.8f), ImVec2(1,1)));
# endif

        std::string _str_label(_label);
        std::string _gui_label(_label);
        _str_label += std::to_string(pinID);
        _str_label += std::to_string(_pinFlag);

        // update node active pin
        if(ImGui::IsItemClicked()){ // || ImGui::IsItemHovered()
            activePin = _str_label;
            activePinType = _type;
        }


        // Let this pin be draggable
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoHoldToOpenOthers|ImGuiDragDropFlags_SourceNoPreviewTooltip)){
            // draw dragging link creation
            if( activePin == _str_label ){ // draw link from active pin only ( last clicked )

                if(_pinFlag==ImGuiExNodePinsFlags_Right){ // drag new links ( only from outlets )

                    fromObjectID = nodeID;
                    outletPinID = pinID;

                    connectType = 1;

                    // PAYLOAD
                    static int tmpNum=777;
                    ImGui::SetDragDropPayload(IMGUI_PAYLOAD_TYPE_PIN_FLOAT, &tmpNum, sizeof(int)); // Set payload to carry the index of our item (could be anything)

                    // add connecting link
                    auto connectingColor = ImGui::ColorConvertU32ToFloat4(_color);
                    connectingColor.w = 0.4f;
                    const LinkBezierData link_data = get_link_renderable(pinLayout.curDrawPos + ImVec2( IMGUI_EX_NODE_PIN_WIDTH * -.5f, pinLayout.pinSpace.y * .5f),ImGui::GetMousePos(),IMGUI_EX_NODE_LINK_LINE_SEGMENTS_PER_LENGTH);
                    canvasDrawList->AddBezierCurve(link_data.bezier.p0,link_data.bezier.p1,link_data.bezier.p2,link_data.bezier.p3,ImGui::ColorConvertFloat4ToU32(connectingColor),IMGUI_EX_NODE_LINK_THICKNESS,link_data.num_segments);

                    // add link info
                    std::string _temp = _type+" "+_gui_label;
                    ImVec2 tempPos = ImGui::GetMousePos() - (ImGui::GetMousePos() - (pinLayout.curDrawPos + ImVec2( IMGUI_EX_NODE_PIN_WIDTH * -.5f, pinLayout.pinSpace.y * .5f)))/2.0f - ImGui::CalcTextSize(_temp.c_str())/2.0f;
                    canvasDrawList->AddRectFilled(tempPos + ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH),tempPos + ImGui::CalcTextSize(_temp.c_str()) + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH),IM_COL32(40,40,40,180) );
                    canvasDrawList->AddText( tempPos , _color, _temp.c_str() );
                }
                else if(_pinFlag==ImGuiExNodePinsFlags_Left && _connected && !_linksData.empty()){ // change previously created links ( only from inlets )

                    fromObjectID = _linksData.at(0)._fromObjectID;
                    outletPinID = _linksData.at(0)._fromPinID;

                    connectType = 2;
                    linkID = _linksData.at(0)._linkID;

                    // PAYLOAD
                    static int tmpNum=777;
                    ImGui::SetDragDropPayload(IMGUI_PAYLOAD_TYPE_PIN_FLOAT, &tmpNum, sizeof(int)); // Set payload to carry the index of our item (could be anything)

                    // retrieve previously connected link
                    auto connectingColor = ImGui::ColorConvertU32ToFloat4(_color);
                    connectingColor.w = 0.4f;
                    const LinkBezierData link_data = get_link_renderable(canvasView.translation+(_linksData.at(0)._toPinPosition*canvasView.scale),ImGui::GetMousePos(),IMGUI_EX_NODE_LINK_LINE_SEGMENTS_PER_LENGTH);
                    canvasDrawList->AddBezierCurve(link_data.bezier.p0,link_data.bezier.p1,link_data.bezier.p2,link_data.bezier.p3,ImGui::ColorConvertFloat4ToU32(connectingColor),IMGUI_EX_NODE_LINK_THICKNESS,link_data.num_segments);

                    // add link info
                    std::string _temp = _type+" "+_linksData.at(0)._linkLabel;
                    ImVec2 tempPos = ImGui::GetMousePos() - (ImGui::GetMousePos() - (canvasView.translation+(_linksData.at(0)._toPinPosition*canvasView.scale)))/2.0f - ImGui::CalcTextSize(_temp.c_str())/2.0f;
                    canvasDrawList->AddRectFilled(tempPos + ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH),tempPos + ImGui::CalcTextSize(_temp.c_str()) + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH),IM_COL32(40,40,40,180) );
                    canvasDrawList->AddText( tempPos , _color, _temp.c_str() );

                }

            }

            ImGui::EndDragDropSource();
        }

        // Accept other pins dropping on this
        if (ImGui::BeginDragDropTarget()){

            if(activePinType == _type){

                static int tmpAccept = 0;
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_PIN_FLOAT,ImGuiDragDropFlags_AcceptNoDrawDefaultRect)){ // ImGuiDragDropFlags_AcceptNoDrawDefaultRect

                    if(_pinFlag==ImGuiExNodePinsFlags_Left){ // only on inlets
                        memcpy((float*)&tmpAccept, payload->Data, sizeof(int));

                        //std::cout << "ACCEPTED = " << tmpAccept << " from object " << fromObjectID << ", from OUTLET PIN " << outletPinID << " to object ID " << nodeID << " to INLET PIN " << pinID << std::endl;

                        // connect/reconnect
                        connectData.connectType = connectType;
                        connectData.linkID = linkID;
                        connectData.fromObjectID = fromObjectID;
                        connectData.fromOutletPinID = outletPinID;
                        connectData.toObjectID = nodeID;
                        connectData.toInletPinID = pinID;

                        // reset selected links
                        for(int i=0;i<_linksData.size();i++){
                            std::vector<int>::iterator it = std::find(selected_links.begin(), selected_links.end(),_linksData.at(i)._linkID);
                            if (it!=selected_links.end()){
                                selected_links.erase(it);
                            }
                        }

                    }

                    activePin = "";
                    activePinType = "";
                    connectType = 0;

                }

            }else{
                if(ImGui::GetIO().MouseReleased[0]){
                    activePinType = "";
                    connectType = 0;
                }
            }

            ImGui::EndDragDropTarget();


        }

    }

    // Set position of pin so user can draw it.
    //float pinSpace = (ImGui::IsItemHovered()) ? IMGUI_EX_NODE_PIN_WIDTH_HOVERED : IMGUI_EX_NODE_PIN_WIDTH;
    float pinSpace = IMGUI_EX_NODE_PIN_WIDTH;

    // Draw pin

    // Left side (INLETS)
    if( _pinFlag==ImGuiExNodePinsFlags_Left ){
        _pinPosition = pinLayout.curDrawPos + ImVec2( IMGUI_EX_NODE_PIN_WIDTH * .5f, pinLayout.pinSpace.y * .5f) + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,0);

        nodeDrawList->AddCircleFilled(_pinPosition, pinSpace * .5f, _color, 6);

        if(ImGui::GetMousePos().x > _pinPosition.x-(pinLayout.pinSpace.x*.5f) && ImGui::GetMousePos().x < _pinPosition.x+(pinLayout.pinSpace.x*.5f) && ImGui::GetMousePos().y > _pinPosition.y-(pinLayout.pinSpace.y*.5f) && ImGui::GetMousePos().y < _pinPosition.y+(pinLayout.pinSpace.y*.5f)){
            if(activePinType == _type || activePinType == ""){
                nodeDrawList->AddCircle(_pinPosition,pinSpace * 0.9f, _color, 6);
                ImVec2 tempPos = _pinPosition - ImVec2(pinSpace * .5f + IMGUI_EX_NODE_PIN_WIDTH + 6,ImGui::GetTextLineHeight()*-.4f) - ImGui::CalcTextSize(_label);
                canvasDrawList->AddRectFilled(tempPos + ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH),tempPos + ImGui::CalcTextSize(_label) + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH),IM_COL32(40,40,40,180) );
                canvasDrawList->AddText( tempPos, _color, _label);
            }

        }

        if(_connected){
            nodeDrawList->AddCircle(_pinPosition,pinSpace * 0.9f, _color, 6);
        }

    }

    // right side (OUTLETS)
    else if( _pinFlag==ImGuiExNodePinsFlags_Right ){
        _pinPosition = pinLayout.curDrawPos + ImVec2( IMGUI_EX_NODE_PIN_WIDTH * -.5f, pinLayout.pinSpace.y * .5f);

        nodeDrawList->AddCircleFilled(_pinPosition, pinSpace * .5f, _color, 6);

        // draw links (OUTLETS to INLETS ONLY)
        for(int i=0;i<_linksData.size();i++){
            const LinkBezierData link_data = get_link_renderable(_pinPosition, canvasView.translation+(_linksData.at(i)._toPinPosition*canvasView.scale), IMGUI_EX_NODE_LINK_LINE_SEGMENTS_PER_LENGTH);

            const bool is_hovered = is_mouse_hovering_near_link(link_data.bezier);

            if(ImGui::IsMouseClicked(0) && !isAnyCanvasNodeHovered){
                if (is_hovered){
                    if (std::find(selected_links.begin(), selected_links.end(),_linksData.at(i)._linkID)==selected_links.end()){
                        selected_links.push_back(_linksData.at(i)._linkID);
                    }
                }else if(!is_hovered && !ImGui::GetIO().KeyShift){
                    std::vector<int>::iterator it = std::find(selected_links.begin(), selected_links.end(),_linksData.at(i)._linkID);
                    if (it!=selected_links.end()){
                        selected_links.erase(it);
                    }
                }
            }


            ImU32 _tempColor = _color;
            if (std::find(selected_links.begin(), selected_links.end(),_linksData.at(i)._linkID)!=selected_links.end()){ // selected
                _tempColor = IM_COL32(255,0,0,255);
            }

            canvasDrawList->AddBezierCurve(link_data.bezier.p0, link_data.bezier.p1, link_data.bezier.p2, link_data.bezier.p3, _tempColor, IMGUI_EX_NODE_LINK_THICKNESS, link_data.num_segments);
        }

        // draw labels
        if(ImGui::GetMousePos().x > _pinPosition.x-IMGUI_EX_NODE_PIN_WIDTH_HOVERED && ImGui::GetMousePos().x < _pinPosition.x+IMGUI_EX_NODE_PIN_WIDTH_HOVERED && ImGui::GetMousePos().y > _pinPosition.y-IMGUI_EX_NODE_PIN_WIDTH_HOVERED && ImGui::GetMousePos().y < _pinPosition.y+IMGUI_EX_NODE_PIN_WIDTH_HOVERED){
            if(connectType == 0){
                nodeDrawList->AddCircle(_pinPosition,pinSpace * 0.9f, _color, 6);
                ImVec2 tempPos = _pinPosition + ImVec2(pinSpace * .5f + 6,ImGui::GetTextLineHeight()*-.5f);
                canvasDrawList->AddRectFilled(tempPos + ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH),tempPos + ImGui::CalcTextSize(_label) + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH),IM_COL32(40,40,40,180) );
                canvasDrawList->AddText( tempPos, _color, _label);
            }
        }

        // draw pin connected
        if(_connected){
            nodeDrawList->AddCircle(_pinPosition,pinSpace * 0.9f, _color, 6);
        }


    }
    pinLayout.curDrawPos += ImVec2(0,pinLayout.pinSpace.y);

    // Move back to center column
    if( _pinFlag==ImGuiExNodePinsFlags_Right ) ImGui::NextColumn(); // left column
    ImGui::NextColumn(); // center column

    // Restore cursor
    ImGui::SetCursorScreenPos(cursorBackup);

    // reset if drag&drop on self
    if(ImGui::GetIO().MouseReleased[0] && ImGui::IsItemHovered() && connectData.toObjectID == -1){
        activePinType = "";
        connectType = 0;
    }

    // remove link if drag from connected inlet and drop on canvas
    if(ImGui::GetIO().MouseReleased[0] && !ImGui::IsAnyItemHovered() && !ImGui::IsAnyItemActive() && !ImGui::IsAnyItemFocused() && !ImGui::IsAnyWindowHovered() && connectType == 2){
        connectData.connectType = 3;
        connectData.linkID = linkID;

        activePinType = "";
        connectType = 0;
    }

    return connectData;*/
    return ImGuiEx::NodeConnectData();
}

// Modified proposal by @daandelange
ImGuiExNodePinResponse ImGuiEx::NodeCanvas::AddNodePin( const char* _dragDropData, const char* _pinLabel, ImVec2& _pinPosition, const char* _linkLabel, const int& _linkTypeId, const ImU32& _pinColor, bool _pinIsConnected, const ImGuiExNodePinsFlags_& _pinFlag ){

    // Check ImGui Callstack
    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
    IM_ASSERT(_pinFlag == ImGuiExNodePinsFlags_Left || _pinFlag == ImGuiExNodePinsFlags_Right); // Only left / right pins can be created (not both)
    IM_ASSERT(curNodeData.pinsFlags & _pinFlag); // Node was not created with correct flags

    // Choose a side
    PinLayout& pinLayout = (_pinFlag==ImGuiExNodePinsFlags_Left) ? curNodeData.leftPins : curNodeData.rightPins;
    // Backup cursor
    static ImVec2 cursorBackup;
    cursorBackup = ImGui::GetCursorScreenPos();

    // Note: Statics prevent re-allocation on every frame
    static std::string returnValue;
    returnValue = "";
    static ImGuiExNodePinActionFlags_ returnFlag;
    returnFlag = ImGuiExNodePinActionFlags_None;
    static bool pinIsBeingDragged;
    pinIsBeingDragged = false;
    static bool pinIsBeingDragHovered;
    pinIsBeingDragHovered = false;
    static bool isDragAcceptable;
    isDragAcceptable = false;

    // Move to column
    ImGui::NextColumn(); // we're in the right col now
    if( _pinFlag==ImGuiExNodePinsFlags_Left ) ImGui::NextColumn(); // we're in the left column now

    // Need to pushID() for better drag&drop support
    ImGui::PushID(_dragDropData);

    // Hover interaction
    if(pinLayout.pinSpace.x > 0){
        if( _pinFlag==ImGuiExNodePinsFlags_Left ){
            ImGui::SetCursorScreenPos( pinLayout.curDrawPos  );
        }
        else {
            ImGui::SetCursorScreenPos( pinLayout.curDrawPos + ImVec2( -pinLayout.pinSpace.x, 0)  );
        }

        // Note: ImMax below is used because buttons fail with 0 size.
# if __IMGUI_EX_NODECANVAS_DEBUG__
        ImGui::Button( (_pinFlag==ImGuiExNodePinsFlags_Left)?"##inletBtnLeft":"##inletBtnRight", ImMax(ImVec2(pinLayout.pinSpace.x,pinLayout.pinSpace.y), ImVec2(1,1)));//pinLayout.pinSpace);
# else
        ImGui::InvisibleButton( (_pinFlag==ImGuiExNodePinsFlags_Left)?"##inletBtnLeft":"##inletBtnRight", ImMax(ImVec2(pinLayout.pinSpace.x,pinLayout.pinSpace.y*.8f), ImVec2(1,1)));
# endif

        // Let this pin be draggable
        if( ImGui::BeginDragDropSource( ImGuiDragDropFlags_SourceNoHoldToOpenOthers | ImGuiDragDropFlags_SourceNoPreviewTooltip )){
            // Note : while dragging, BeginDragDropSource() is true every frame (because you can draw the tooltip in it)

            pinIsBeingDragged = true;
            // Set only when draggin starts
            if(activeLinkSourcePinUID != _dragDropData){

                // Populate the payload
                static std::string payloadTitle;
                payloadTitle = ( _pinFlag==ImGuiExNodePinsFlags_Left) ? IMGUI_PAYLOAD_TITLE_INLET : IMGUI_PAYLOAD_TITLE_OUTLET;
                payloadTitle.append( std::to_string(_linkTypeId) );
                // Set payload to carry the _dragDropData, usually a uniqueID (could be anything)
                ImGui::SetDragDropPayload( payloadTitle.c_str(), (std::string::value_type*)_dragDropData, sizeof(std::string::value_type*)*strlen(_dragDropData), ImGuiCond_Always);
                //std::cout << "Sending PAYLOAD = " << payloadTitle << " from pin " << _dragDropData << std::endl;

                // Remember that we're dragging
                activeLinkSourcePinUID = _dragDropData;
                activeLink.linkColor = _pinColor;
                activeLink.linkLabel = _linkLabel;

                // todo: pinLayout.curDrawPos seems not to be set on beginNode() or something. The first one often glitches, and the cursor is seemingly at the previous pin location.
                if(_pinFlag==ImGuiExNodePinsFlags_Left){
                    //activeLink.fromPinPos = ImGui::GetMousePos();
                    activeLink.toPinPos = pinLayout.curDrawPos + ImVec2( IMGUI_EX_NODE_PIN_WIDTH * -.5f, pinLayout.pinSpace.y * .5f);
                }
                else {
                    activeLink.fromPinPos = pinLayout.curDrawPos + ImVec2( IMGUI_EX_NODE_PIN_WIDTH * -.5f, pinLayout.pinSpace.y * .5f);
                    //activeLink.toPinPos = ImGui::GetMousePos();
                }
            }

            // Draw the link preview (pin being dragged)
            if( this->activeLinkSourcePinUID == _dragDropData ){ // draw link from active pin only ( last dragged )
                // Cancel drag ?
                if( !ImGui::IsMouseDragging( ImGuiMouseButton_Left ) ){
                    //std::cout << "Reset drag by pin (on another frame) " << _dragDropData << std::endl;
                    activeLinkSourcePinUID = "";
                    pinIsBeingDragged = false;
                }
                else {
                    // Update the activeLink information
                    if( _pinFlag==ImGuiExNodePinsFlags_Left ){
                        activeLink.fromPinPos = ImGui::GetMousePos();
                    }
                    else {
                        activeLink.toPinPos = ImGui::GetMousePos();
                    }

                    // Draw dragging link
                    auto connectingColor = activeLink.linkColor;//ImGui::ColorConvertU32ToFloat4(activeLink.linkColor);
                    setColorTransparency(connectingColor, 128);//connectingColor.w = 0.4f;
                    const LinkBezierData link_data = get_link_renderable( activeLink.fromPinPos, activeLink.toPinPos,IMGUI_EX_NODE_LINK_LINE_SEGMENTS_PER_LENGTH);
                    ImGui::GetForegroundDrawList()->AddBezierCurve(link_data.bezier.p0,link_data.bezier.p1,link_data.bezier.p2,link_data.bezier.p3,connectingColor,IMGUI_EX_NODE_LINK_THICKNESS,link_data.num_segments);

                    // Draw link info
                    //ImVec2 tempPos = activeLink.fromPinPos - (activeLink.fromPinPos - (activeLink.toPinPos + ImVec2( IMGUI_EX_NODE_PIN_WIDTH * -.5f, pinLayout.pinSpace.y * .5f)))*.5f - ImGui::CalcTextSize(activeLink.linkLabel.c_str())*.5f; // Use this to place in middle of cable
                    ImVec2 labelTextSize = ImGui::CalcTextSize( activeLink.linkLabel.c_str() );
                    ImVec2 bezierSize = ImMax( ImAbs(link_data.bezier.p3 - link_data.bezier.p0), ImVec2(1,1));
                    float extraPercentage = std::abs( (labelTextSize.x*.5f)/ImMax(bezierSize.x,bezierSize.y) ) * ((_pinFlag==ImGuiExNodePinsFlags_Left)? 1.f : -1.f);
                    ImVec2 tempPos = eval_bezier( ImClamp(((_pinFlag==ImGuiExNodePinsFlags_Left)?.1f:.9f)+extraPercentage,0.f,1.f), link_data.bezier ); // Use this to position the cable close to the mouse
                    tempPos -= labelTextSize*.5f;
                    ImGui::GetForegroundDrawList()->AddRectFilled(tempPos + ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH), tempPos + labelTextSize + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH), IM_COL32(40,40,40,180) );
                    ImGui::GetForegroundDrawList()->AddText( tempPos , activeLink.linkColor, activeLink.linkLabel.c_str() );
                }
            }

            ImGui::EndDragDropSource();
        }
        // Check if the drag handle was dropped
        else if( activeLinkSourcePinUID == _dragDropData ){
            // Reset
            if(!ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !ImGui::IsDragDropPayloadBeingAccepted() ){
                // Don't reset this at the end of dragging, or it will erase before the other gets it
                activeLinkSourcePinUID = "";
                //std::cout << "Reset drag (drag dropped) by " << _dragDropData << std::endl;
            }
            pinIsBeingDragged = false;
        }

        // Cannot connect to self (inlet and outlet mixed)
        if( activeLinkSourcePinUID.size() > 0 && activeLinkSourcePinUID != _dragDropData ){
            // Accept other pins dropping on this
            if (ImGui::BeginDragDropTarget()){
                pinIsBeingDragHovered = true;
                //std::cout << "DropHovered=" << _dragDropData << std::endl;
                // Get the payload data (on drop)
                static std::string payloadTitle;
                payloadTitle = ((_pinFlag==ImGuiExNodePinsFlags_Left) ? IMGUI_PAYLOAD_TITLE_OUTLET : IMGUI_PAYLOAD_TITLE_INLET );
                payloadTitle.append( std::to_string(_linkTypeId) );
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadTitle.c_str(),ImGuiDragDropFlags_AcceptNoDrawDefaultRect | ImGuiDragDropFlags_AcceptBeforeDelivery)){ // ImGuiDragDropFlags_AcceptNoDrawDefaultRect
                    //static char* tmpAccept = nullptr;
                    //memcpy((char**)&tmpAccept, payload->Data, sizeof(char*));
                    isDragAcceptable = true;

                    // Handle data on drop
                    if( payload->IsDelivery() ){
                    //if(_pinFlag==ImGuiExNodePinsFlags_Left){ // only on inlets

                        // Set return values
                        std::string::value_type* parsedData = static_cast<std::string::value_type*>(payload->Data);

                        if( parsedData != nullptr ){
                            returnValue = parsedData;
                            returnFlag = ImGuiExNodePinActionFlags_ConnectPin;

                            std::cout << "Got Payload ! = " << returnValue << "/" << payloadTitle << " on pin " << _dragDropData << std::endl; // tmp

                        }
                        else {
                            // failed parsing payload ! (connection cancelled)
                            std::cout << "[Notice] ImGuiEx::NodeCanvas::AddNodePin() failed parsing the payload..." << std::endl;                        }

                        // Reset
                        //std::cout << "Payload reset by accepting pin." << std::endl;
                        activeLinkSourcePinUID = "";
                        pinIsBeingDragHovered = false;

                    }

//                    // Draw target connection info label (pin being drag-hovered with an acceptable type)
//                    if( payload->IsPreview() ) {
//                        ImVec2 labelTextSize = ImGui::CalcTextSize( _pinLabel );
//                        if(_pinFlag==ImGuiExNodePinsFlags_Left){

//                        }
//                        ImVec2 tempPos = ImVec2(
//                            (_pinFlag==ImGuiExNodePinsFlags_Left) ? pinLayout.region.Max.x/* - labelTextSize.x */ + IMGUI_EX_NODE_PIN_WIDTH*.5f : pinLayout.region.Min.x - labelTextSize.x - IMGUI_EX_NODE_PIN_WIDTH*.5f,
//                            pinLayout.curDrawPos.y + (pinLayout.pinSpace.y * .5f) - (labelTextSize.y*.5f)/* - IMGUI_EX_NODE_PIN_WIDTH*.5f*/
//                        );

//                        ImGui::GetForegroundDrawList()->AddRectFilled(tempPos + ImVec2( - pinLayout.pinSpace.x,-IMGUI_EX_NODE_PIN_WIDTH), tempPos + labelTextSize + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH), IM_COL32(40,40,40,180) );
//                        ImGui::GetForegroundDrawList()->AddText( tempPos /*+ ImVec2(IMGUI_EX_NODE_PIN_WIDTH,0)*/ , _pinColor, _pinLabel );
//                    }

                }
                else {
                    // Reset
                    if(!ImGui::IsMouseDragging(ImGuiMouseButton_Left)){
                        //std::cout << "Reset drag (after hover) by " << _dragDropData << std::endl;
                        activeLinkSourcePinUID = "";
                        pinIsBeingDragHovered = false;
                    }
                }

                ImGui::EndDragDropTarget();
            }
        }

        // draw denial dialog ? (not used, kept for reference)
        if(false && !isDragAcceptable && pinIsBeingDragHovered){
            // todo: make this look better
            static std::string text = "-x-";
            static ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
            ImVec2 tmpPos = ImVec2( pinLayout.region.Min.x, pinLayout.curDrawPos.y);// /*+ ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH)*/;//( pinLayout.region.GetCenter().x , pinLayout.curDrawPos.y-);
            ImGui::GetForegroundDrawList()->AddRectFilled( tmpPos, tmpPos + pinLayout.pinSpace, IM_COL32(0,0,0,180) );
            ImGui::GetForegroundDrawList()->AddText(tmpPos+ImVec2(pinLayout.region.GetSize().x*.5f - textSize.x*.5f, pinLayout.pinSpace.y*.5f - textSize.y*.5f), IM_COL32(255,0,0,255), text.c_str());
        }
    }

    // Update the pin position so it draws at the correct location
    //float pinSpace = (ImGui::IsItemHovered()) ? IMGUI_EX_NODE_PIN_WIDTH_HOVERED : IMGUI_EX_NODE_PIN_WIDTH;
    //float pinSpace = IMGUI_EX_NODE_PIN_WIDTH;

    // Send pin location to parent
    _pinPosition = (_pinFlag==ImGuiExNodePinsFlags_Left) ?
                // PREV DRAW POS.END           ( MOVE the CENTER OF PIN ZONE   ) + ( CENTER OF PIN ZONE        )  ( CENTER OF PIN ZONE         )
                pinLayout.curDrawPos + ImVec2( (IMGUI_EX_NODE_PIN_WIDTH * +.0f ) + (pinLayout.pinSpace.x * +.5f), ( pinLayout.pinSpace.y * .5f )):
                pinLayout.curDrawPos + ImVec2( (IMGUI_EX_NODE_PIN_WIDTH * -.0f ) + (pinLayout.pinSpace.x * -.5f), ( pinLayout.pinSpace.y * .5f ));

    // Draw target connection info label (pin being drag-hovered with an acceptable type)
    if( pinIsBeingDragHovered && isDragAcceptable ){
        ImVec2 labelTextSize = ImGui::CalcTextSize( _pinLabel );

        // Text is aligned inside the node, for a more intuitive data-flow direction presentation
        ImVec2 labelTextPos = ImVec2(
            // X coords
            (_pinFlag==ImGuiExNodePinsFlags_Left) ?
                    pinLayout.region.Max.x /*- labelTextSize.x*/  + IMGUI_EX_NODE_PIN_WIDTH : // LEFT PINS X
                    pinLayout.region.Min.x - labelTextSize.x - IMGUI_EX_NODE_PIN_WIDTH // RIGHT PINS X
            // Y Coords
            ,pinLayout.curDrawPos.y + (pinLayout.pinSpace.y * .5f) - (labelTextSize.y*0.5f)/* - IMGUI_EX_NODE_PIN_WIDTH*.5f*/
        );

        ImGui::GetForegroundDrawList()->AddRectFilled( labelTextPos + ImVec2( /*- pinLayout.pinSpace.x*/ - (IMGUI_EX_NODE_PIN_WIDTH),-IMGUI_EX_NODE_PIN_WIDTH), labelTextPos + labelTextSize + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH), IM_COL32(40,40,40,180) );
        ImGui::GetForegroundDrawList()->AddText( labelTextPos /*+ ImVec2(IMGUI_EX_NODE_PIN_WIDTH,0)*/ , _pinColor, _pinLabel );
    }
    // Draw target connection info label (else, any hover = draw label)
    else if( ImGui::IsItemHovered() ){ // any hover = draw label
        ImVec2 labelTextSize = ImGui::CalcTextSize( _pinLabel );

        // Text is aligned outside the node, not to mess up with the node content zone
        ImVec2 labelTextPos = ImVec2(
            // X coords
            (_pinFlag==ImGuiExNodePinsFlags_Left) ?
            //      STARTING BOUNDARY         TEXT WIDTH        TEXT MARGIN
                    pinLayout.region.Min.x  - labelTextSize.x   - IMGUI_EX_NODE_PIN_WIDTH : // LEFT PINS X
                    pinLayout.region.Max.x/* - labelTextSize.x*/ + IMGUI_EX_NODE_PIN_WIDTH // RIGHT PINS X
            // Y Coords
            ,pinLayout.curDrawPos.y + (pinLayout.pinSpace.y * .5f) - (labelTextSize.y*0.5f)/* - IMGUI_EX_NODE_PIN_WIDTH*.5f*/
        );

        ImGui::GetForegroundDrawList()->AddRectFilled(
                    // Min
                    labelTextPos + ImVec2( -IMGUI_EX_NODE_PIN_WIDTH, -IMGUI_EX_NODE_PIN_WIDTH),
                    // Max
                    labelTextPos + labelTextSize + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH),
                    IM_COL32(40,40,40,180)
        );
        ImGui::GetForegroundDrawList()->AddText( labelTextPos /*+ ImVec2(IMGUI_EX_NODE_PIN_WIDTH,0)*/ , _pinColor, _pinLabel );
    }

    // Draw pin
    if( pinIsBeingDragHovered && !isDragAcceptable ){ // Uncompatible hover appearance
        ImGui::GetForegroundDrawList()->AddCircleFilled( _pinPosition, IMGUI_EX_NODE_PIN_WIDTH * .6f, IM_COL32(255,0,0,200), 6);//IM_COL32(126,126,126,200), 6);
    }
    else if( pinIsBeingDragged || pinIsBeingDragHovered || ImGui::IsItemHovered() ){ // Dragging or compatible hover appearance
        ImGui::GetForegroundDrawList()->AddCircleFilled( _pinPosition, IMGUI_EX_NODE_PIN_WIDTH * .5f, _pinColor, 6);
        ImGui::GetForegroundDrawList()->AddCircle( _pinPosition, IMGUI_EX_NODE_PIN_WIDTH * (ImGui::IsItemHovered()?.9f:1.f), _pinColor, 6);
    }
    else {
        // default appearance
        nodeDrawList->AddCircleFilled( _pinPosition, IMGUI_EX_NODE_PIN_WIDTH * .5f, _pinColor, 6);
        // Extra connected appearance
        if( _pinIsConnected ){
            nodeDrawList->AddCircle( _pinPosition, IMGUI_EX_NODE_PIN_WIDTH * 0.9f, _pinColor, 6);
        }
    }


    // draw labels (old code, kept in case of reversing changes)
//    if(ImGui::GetMousePos().x > _pinPosition.x-IMGUI_EX_NODE_PIN_WIDTH_HOVERED && ImGui::GetMousePos().x < _pinPosition.x+IMGUI_EX_NODE_PIN_WIDTH_HOVERED && ImGui::GetMousePos().y > _pinPosition.y-IMGUI_EX_NODE_PIN_WIDTH_HOVERED && ImGui::GetMousePos().y < _pinPosition.y+IMGUI_EX_NODE_PIN_WIDTH_HOVERED){
        // old right label code
//        if(connectType == 0){
//            nodeDrawList->AddCircle(_pinPosition,pinSpace * 0.9f, _pinColor, 6);
//            ImVec2 tempPos = _pinPosition + ImVec2(pinSpace * .5f + 6,ImGui::GetTextLineHeight()*-.5f);
//            ImGui::GetForegroundDrawList()->AddRectFilled(tempPos + ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH),tempPos + ImGui::CalcTextSize(_pinLabel) + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH),IM_COL32(40,40,40,180) );
//            ImGui::GetForegroundDrawList()->AddText( tempPos, _pinColor, _pinLabel);
//        }

        // old left label code
//        if(ImGui::GetMousePos().x > _pinPosition.x-(pinLayout.pinSpace.x*.5f) && ImGui::GetMousePos().x < _pinPosition.x+(pinLayout.pinSpace.x*.5f) && ImGui::GetMousePos().y > _pinPosition.y-(pinLayout.pinSpace.y*.5f) && ImGui::GetMousePos().y < _pinPosition.y+(pinLayout.pinSpace.y*.5f)){
//            if(activePinType == _linkLabel || activePinType == ""){
//                nodeDrawList->AddCircle(_pinPosition,pinSpace * 0.9f, _pinColor, 6);
//                ImVec2 tempPos = _pinPosition - ImVec2(pinSpace * .5f + IMGUI_EX_NODE_PIN_WIDTH + 6,ImGui::GetTextLineHeight()*-.4f) - ImGui::CalcTextSize(_pinLabel);
//                canvasDrawList->AddRectFilled(tempPos + ImVec2(-IMGUI_EX_NODE_PIN_WIDTH,-IMGUI_EX_NODE_PIN_WIDTH),tempPos + ImGui::CalcTextSize(_pinLabel) + ImVec2(IMGUI_EX_NODE_PIN_WIDTH,IMGUI_EX_NODE_PIN_WIDTH),IM_COL32(40,40,40,180) );
//                canvasDrawList->AddText( tempPos, _pinColor, _pinLabel);
//            }
//        }
//    }

    // Increment pinspace
    pinLayout.curDrawPos += ImVec2(0,pinLayout.pinSpace.y);

    ImGui::PopID();

    // Move back to center column
    if( _pinFlag==ImGuiExNodePinsFlags_Right ) ImGui::NextColumn(); // Now we're in the left column
    ImGui::NextColumn(); // Now we're in the center column

    // Restore cursor
    ImGui::SetCursorScreenPos(cursorBackup);

    // reset if drag&drop on self
//    if(ImGui::GetIO().MouseReleased[0] && ImGui::IsItemHovered() ){
//        activePinType = "";
//        //connectType = 0;
//    }

    // remove link if drag from connected inlet and drop on canvas
//    if(ImGui::GetIO().MouseReleased[0] && !ImGui::IsAnyItemHovered() && !ImGui::IsAnyItemActive() && !ImGui::IsAnyItemFocused() && !ImGui::IsAnyWindowHovered() && connectType == 2){
//        connectData.connectType = 3;
//        connectData.linkID = linkID;

//        activePinType = "";
//        connectType = 0;
//    }

    //return connectData;
    return ImGuiExNodePinResponse( returnFlag, returnValue.c_str() );
}

// Todo: allow rendering links when the node is inactive ?
ImGuiExNodeLinkActionFlags_ ImGuiEx::NodeCanvas::AddLink(const ImVec2& _fromPos, const ImVec2& _toPos, const ImU32& _color, const char* _label){
    // draw links (OUTLETS to INLETS ONLY)
    const LinkBezierData link_data = get_link_renderable(_fromPos, _toPos, IMGUI_EX_NODE_LINK_LINE_SEGMENTS_PER_LENGTH);

    // Make an UID from 2 position pointers (which combined should be unique)
    std::uintptr_t uniqueNumber = reinterpret_cast<std::uintptr_t>(&_fromPos) + reinterpret_cast<std::uintptr_t>(&_toPos);
    static std::vector<std::uintptr_t>::iterator existingSelection;
    existingSelection = std::find(selectedLinks.begin(), selectedLinks.end(), uniqueNumber );
    bool linkIsSelected; linkIsSelected = existingSelection != selectedLinks.end();

    // Todo: Handle link out-of-sight (return early)

    // Handle link selection
    if(ImGui::IsMouseClicked( ImGuiMouseButton_Left ) && !isAnyCanvasNodeHovered){
        // Calc hover state of bezier
        const bool is_hovered = is_mouse_hovering_near_link(link_data.bezier);

        // Manage selection / deselection
        if (is_hovered){
            // select if not existing
            if (!linkIsSelected){ // not selected
                if(!ImGui::GetIO().KeyShift) selectedLinks.resize(0); // deselect others
                if(selectedNodes.size()>0) selectedNodes.resize(0); // deselect nodes
                selectedLinks.push_back(uniqueNumber);
                linkIsSelected = true;
                existingSelection = selectedLinks.end()-1;
                //std::cout << "Selected a single link ! UID="<< uniqueNumber << std::endl;
            }
            else { // link is selected
                // remove from selection if shift pressed
                if( ImGui::GetIO().KeyShift) {
                    selectedLinks.erase( existingSelection );
                    //std::cout << "Deselected a single link ! UID="<< uniqueNumber << std::endl;
                    linkIsSelected = false;
                    existingSelection = selectedLinks.end();
                }
            }
        }
        // Not hovered (clicked on canvas bg)
        else {
            // Remove link from selection
            if( linkIsSelected && !ImGui::GetIO().KeyShift){
                selectedLinks.erase(existingSelection);
                linkIsSelected = false;
            }
        }
    }

    // Handle Link deletion ?
    if( linkIsSelected && ImGui::GetIO().KeysDown[ImGui::GetIO().KeyMap[ImGuiKey_Delete]] && !ImGui::IsAnyItemFocused() ){
        selectedLinks.erase(existingSelection);
        linkIsSelected = false;

        // Send return values
        return ImGuiExNodeLinkActionFlags_Disconnect;
    }

    // draw selection wire
    if( linkIsSelected ){
        ImU32 selectedColor = Darken(_color, .3f);
        canvasDrawList->AddBezierCurve(link_data.bezier.p0, link_data.bezier.p1, link_data.bezier.p2, link_data.bezier.p3, selectedColor, IMGUI_EX_NODE_LINK_THICKNESS*2, link_data.num_segments);
    }
    // Draw regular wire
    canvasDrawList->AddBezierCurve(link_data.bezier.p0, link_data.bezier.p1, link_data.bezier.p2, link_data.bezier.p3, _color, IMGUI_EX_NODE_LINK_THICKNESS, link_data.num_segments);

    // Todo: Handle visualize return value. How to visualize a node ?

    return ImGuiExNodeLinkActionFlags_None;
};

bool ImGuiEx::NodeCanvas::BeginNodeMenu(){
    // Check ImGui Callstack
    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
    IM_ASSERT(isDrawingMenu == false); // Forgot to call EndNodeMenu !

    // returns true if menu is open
    bool ret = ImGui::BeginPopup(IMGUI_EX_NODE_MENU_ID);
    if( ret ){
        isDrawingMenu = true;

        // Add separator
        ImGui::Separator();
    }

    return ret;
}
void ImGuiEx::NodeCanvas::EndNodeMenu(){
    // Check ImGui Callstack
    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
    IM_ASSERT(isDrawingMenu == true); // Only call if BeginNodeMenu returned true

    isDrawingMenu = false;
    ImGui::EndPopup();
}

// For drawing content to the node
bool ImGuiEx::NodeCanvas::BeginNodeContent( const ImGuiExNodeView& _renderingView ){
    // Check ImGui Callstack
    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
    IM_ASSERT(isDrawingMenu == false); // Forgot to call EndNodeMenu() !
    IM_ASSERT(isDrawingContent == false);  // Forgot to call EndNodeContent() !

    // Dont allow drawing in invisible nodes
    bool ret = false;
    if( curNodeData.zoomName == ImGuiExNodeZoom_Invisible ){
        ret = false;
    }
    // User can draw to imploded when there are no pins...
    else if( curNodeData.zoomName == ImGuiExNodeZoom_Imploded ){

        if(curNodeData.pinsFlags == ImGuiExNodePinsFlags_None){ // No pins
            ret = true;
        }
    }
    // Zoom level accepts content
    else if( curNodeData.zoomName > ImGuiExNodeZoom_Imploded ){
        // If asked view includes current view, for custom rendering.
        ret = ( _renderingView & curNodeData.viewName );
    }
    // Any other case = no drawing !
    else {
        ret = false;
    }

    isDrawingContent = ret;
    return ret;
}
void ImGuiEx::NodeCanvas::EndNodeContent(){
    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
    IM_ASSERT(isDrawingMenu == false); // Huh ?
    IM_ASSERT(isDrawingContent == true); // // Only call when BeginNodeContent() returned true !

    isDrawingContent = false;

    if(curNodeData.zoomName > ImGuiExNodeZoom_Invisible ){

        // Only pop these if content is drawn
        if( true || curNodeData.zoomName > ImGuiExNodeZoom_Imploded ){
            //ImGui::PopItemWidth();
            ImGui::Dummy(ImVec2(-1,IMGUI_EX_NODE_CONTENT_PADDING)); // Padding bottom
            ImGui::EndColumns();
            ImGui::PopClipRect(); // Inner space + nodes
        }

        // Always pop these ()
        ImGui::PopClipRect();

    }
}

bool ImGuiEx::NodeCanvas::doNodeMenuAction( const ImGuiExNodeMenuActionFlags& _menuItem ){
    IM_ASSERT(isDrawingCanvas == true); // Please Call between Begin() and End()
    IM_ASSERT(isDrawingNode == true); // Please Call between BeginNode() and EndNode()
    IM_ASSERT(!(_menuItem & ImGuiExNodeMenuActionFlags_None) ); // Don't you fool me !
    IM_ASSERT( std::bitset<16>(_menuItem).count() == 1 ); // Max 1 flag at a time !

    return (curNodeData.menuActions & _menuItem);
}


//void ImGuiEx::NodeCanvas::pushNodeWorkRect(){
//    ImGuiWindow* win = ImGui::GetCurrentWindow();
//    canvasWorkRectBackup.Min = win->WorkRect.Min;
//    canvasWorkRectBackup.Max = win->WorkRect.Max;
//    win->WorkRect.Max = curNodeData.innerContentBox.Max - ImVec2(IMGUI_EX_NODE_CONTENT_PADDING,IMGUI_EX_NODE_CONTENT_PADDING);
//    win->WorkRect.Min = curNodeData.innerContentBox.Min + ImVec2(IMGUI_EX_NODE_CONTENT_PADDING,IMGUI_EX_NODE_CONTENT_PADDING);
//}

//void ImGuiEx::NodeCanvas::popNodeWorkRect(){
//    ImGuiWindow* win = ImGui::GetCurrentWindow();
//    win->WorkRect.Max = curNodeData.innerContentBox.Max;
//    win->WorkRect.Min = curNodeData.innerContentBox.Min;
//}
