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

    Made for Mosaic, but could be of use in any other project.
    https://mosaic.d3cod3.org/
==============================================================================*/

// Todo: Make the canvas' methods static so you don't have to store an instance.
// Todo: Add IMGUI_API to public methods

# ifndef __IMGUI_EX_NODECANVAS_H__
# define __IMGUI_EX_NODECANVAS_H__
# define __IMGUI_EX_NODECANVAS_DEBUG__ 0 // enable for debugging layout
# pragma once

# include <imgui.h>
# include <imgui_internal.h> // Access to more advanced ImGui variables.

// Default values. You can override them in imconfig.h
// Everything below is in screen pixels, actual size, non scaled.
# define IMGUI_EX_NODE_MIN_WIDTH 40 // Minimum width. Items cannot be smaller.
# define IMGUI_EX_NODE_MIN_HEIGHT 26 // Maximum height. Items cannot be smaller.
# define IMGUI_EX_NODE_HEADER_HEIGHT 20
# define IMGUI_EX_NODE_HEADER_TOOLBAR_WIDTH 80 // Fixed needed width
# define IMGUI_EX_NODE_MIN_WIDTH_SMALL (IMGUI_EX_NODE_HEADER_TOOLBAR_WIDTH + 40) // Min before entering simplified "imploded" render state. Advised to be 30px+ bigger then IMGUI_EX_NODE_HEADER_TOOLBAR_WIDTH
# define IMGUI_EX_NODE_MIN_WIDTH_NORMAL (IMGUI_EX_NODE_MIN_WIDTH_SMALL + 40)
# define IMGUI_EX_NODE_MIN_WIDTH_LARGE (IMGUI_EX_NODE_MIN_WIDTH_NORMAL + 60)
# define IMGUI_EX_NODE_FOOTER_HEIGHT 6
# define IMGUI_EX_NODE_FOOTER_HANDLE_SIZE 16
# define IMGUI_EX_NODE_CONTENT_PADDING 4
# define IMGUI_EX_NODE_PINS_WIDTH_SMALL 10
# define IMGUI_EX_NODE_PINS_WIDTH_NORMAL 15
# define IMGUI_EX_NODE_PINS_WIDTH_LARGE 30
# define IMGUI_EX_NODE_PIN_WIDTH 8
# define IMGUI_EX_NODE_PIN_WIDTH_HOVERED 12
# define IMGUI_EX_NODE_HOVER_DISTANCE 7
# define IMGUI_EX_NODE_LINK_LINE_SEGMENTS_PER_LENGTH 0.1
# define IMGUI_EX_NODE_LINK_THICKNESS 3

// Other defines
# define IMGUI_EX_NODE_MENU_ID "nodeMenu"
//# define IMGUI_EX_NODE_MENU_ACTION_DELETE 1

// Color helper funcs
static ImVec4 Darken (ImVec4 c, float p){ return ImVec4(fmax(0.f, c.x - 1.0f * p), fmax(0.f, c.y - 1.0f * p), fmax(0.f, c.z - 1.0f *p), c.w); }
static ImVec4 Lighten(ImVec4 c, float p){ return ImVec4(fmax(0.f, c.x + 1.0f * p), fmax(0.f, c.y + 1.0f * p), fmax(0.f, c.z + 1.0f *p), c.w); }
static ImU32  Darken (const ImU32&  c, float p){ return ImGui::ColorConvertFloat4ToU32( Darken (ImColor(c).Value, p) );};
static ImU32  Lighten(const ImU32&  c, float p){ return ImGui::ColorConvertFloat4ToU32( Lighten(ImColor(c).Value, p) );};
inline void setColorTransparency(ImU32& _col, const unsigned int& _transparency ){
    _col &= ~IM_COL32_A_MASK; // Set alpha to 0
    _col |= (((ImU32)_transparency) << IM_COL32_A_SHIFT); // Add alpha to color
}

// Indicates which menu action has triggered, if any.
typedef int ImGuiExNodeMenuActionFlags;
enum ImGuiExNodeMenuActionFlags_ {
    ImGuiExNodeMenuActionFlags_None           = 0,     // No menu actions, do nothing.
    ImGuiExNodeMenuActionFlags_DeleteNode     = 1 << 0,// Delete this node please
    ImGuiExNodeMenuActionFlags_DuplicateNode  = 1 << 1,// Duplicate
    ImGuiExNodeMenuActionFlags_CopyNode       = 1 << 2 // Copy
};

// Indicates which pin action has triggered, if any.
//typedef int ImGuiExNodePinActionFlags;
enum ImGuiExNodePinActionFlags_ {
    ImGuiExNodePinActionFlags_None          = 0,     // No pin actions, do nothing.
    ImGuiExNodePinActionFlags_ConnectPin    = 1 << 0,// Connect
    ImGuiExNodePinActionFlags_DisconnectPin = 1 << 1,// Disconnect, inlets only
    //ImGuiExNodePinActionFlags_ReconnectPin  = 1 << 2 // Reconnect. Note: removed, use connect with logic. (if pin is inlet and pin is connected, then you have a reconnect)
};

// Response data for AddNodePin()
struct ImGuiExNodePinResponse {
    ImGuiExNodePinResponse(const ImGuiExNodePinActionFlags_& _flag=ImGuiExNodePinActionFlags_None, const char* _uid="") : flag(_flag), otherUid(_uid){};
    const ImGuiExNodePinActionFlags_ flag;
    const char* otherUid;
    explicit operator bool() { return this->flag != ImGuiExNodePinActionFlags_None; }; // So you can : if(response){ treat response };
};

enum ImGuiExNodeLinkActionFlags_ {
    ImGuiExNodeLinkActionFlags_None         = 0,      // No pin actions, do nothing.
    ImGuiExNodeLinkActionFlags_Disconnect   = 1 << 0, // Connect
    ImGuiExNodeLinkActionFlags_Visualize    = 1 << 1, // Visualize pin data. Not implemented yet. Todo.
};

typedef int ImGuiExNodePinsFlags;    // -> enum ImGuiExNodePinsFlags_
enum ImGuiExNodePinsFlags_ {
    ImGuiExNodePinsFlags_None  = 0,      // No nodes
    ImGuiExNodePinsFlags_Left  = 1 << 0,  // Will draw nodes on the left
    ImGuiExNodePinsFlags_Right = 1 << 1, // Will draw nodes on the right
    ImGuiExNodePinsFlags_Both = ImGuiExNodePinsFlags_Left | ImGuiExNodePinsFlags_Right, // Not used, can be removed ?
};

typedef unsigned int ImGuiExNodeZoom;    // -> enum ImGuiExNodeZoom_
enum ImGuiExNodeZoom_ {
    // this list doesn't eally need bitmasks, it's more of an ordered list.
    // Dont change the scale order.
    ImGuiExNodeZoom_Invisible  = 0,         // Invisible, out of sight, etc.
    ImGuiExNodeZoom_Imploded   = 1,// << 1, // Minimal visible size, only represent the node, don't show contents.
    ImGuiExNodeZoom_Small      = 2,// << 2, // Minimal view with contents.
    ImGuiExNodeZoom_Normal     = 3,// << 3, // Regular scale
    ImGuiExNodeZoom_Large      = 4,// << 4, // Zoomed scale
    //ImGuiExNodeZoom_FullScreen = 1 << 5, // Zoomed to full screen
};

typedef unsigned int ImGuiExNodeView;    // -> enum ImGuiExNodeView_
enum ImGuiExNodeView_ {
    ImGuiExNodeView_None       = 0,      // Undefined
    ImGuiExNodeView_Params     = 1 << 1, // Settings
    ImGuiExNodeView_Visualise  = 1 << 2, // Visualise node data
    ImGuiExNodeView_Info       = 1 << 3, // Show information and/or stats
    //ImGuiExNodeView_Bypass     = 1 << 4,
    ImGuiExNodeView_Any        = ImGuiExNodeView_Params | ImGuiExNodeView_Visualise | ImGuiExNodeView_Info
};

// extend ImGui in ImGuiEx namespace
namespace ImGuiEx {

// Defines Canvas View data
struct NodeCanvasView {
    ImVec2 translation = ImVec2(0,0);
    float  scale  = 1.0f;
    //ImRect contentRect = ImRect(ImVec2(0,0), ImVec2(0,0));
    //ImRect screenRect = ImRect(ImVec2(0,0), ImVec2(100,100));

    NodeCanvasView() = default;
    NodeCanvasView(const ImVec2& _offset, float _scale) :
        translation(ImFloor(_offset)),
        scale(_scale){}

    void setTransform(const ImVec2& _offset, const float& _scale){
        translation = ImFloor(_offset);
        scale = _scale;
    }
};

// Layout for pins data
struct PinLayout {
    ImRect region;              // Containing zone for all pins
    mutable ImVec2 curDrawPos;  // Cursor location
    unsigned int numPins = 0;   // Number of pins to dispatch in the zone
    ImVec2 pinSpace;            // Size of 1 pin within the region.

    PinLayout() = default;
    PinLayout( const ImVec2& _posMin, const ImVec2& _posMax, const int _numPins=0 ) :
        region(_posMin, _posMax),
        curDrawPos( _posMin ),
        numPins( _numPins ),
        pinSpace( (numPins > 0) ? ImVec2( (region.GetSize() / ImVec2(1,numPins)) ) : ImVec2(0,0) )
        {}
};

// Defines Canvas View data
// All values are scaled to screen, scale is kept for reference.
struct NodeLayoutData {
    ImRect outerContentBox = ImRect(ImVec2(0,0), ImVec2(100,100));
    ImRect innerContentBox = ImRect(ImVec2(0,0), ImVec2(100,100));
    PinLayout leftPins = PinLayout(ImVec2(0,0), ImVec2(0,100), 0);
    PinLayout rightPins = PinLayout(ImVec2(0,0), ImVec2(0,100), 0);
    float  scale  = 1.0f;
    ImGuiExNodeZoom zoomName = ImGuiExNodeZoom_Normal;
    ImGuiExNodeView viewName = ImGuiExNodeView_None;
    ImGuiExNodePinsFlags pinsFlags = ImGuiExNodePinsFlags_None;
    ImGuiExNodeMenuActionFlags menuActions;

    NodeLayoutData() = default;
    NodeLayoutData(const ImVec2& _origin, const ImVec2& _size, const float _scale) :
        outerContentBox(ImFloor(_origin), ImFloor(_origin+_size)),
        innerContentBox(
            ImFloor(ImVec2(_origin.x,_origin.y+IMGUI_EX_NODE_HEADER_HEIGHT)),
            ImFloor(ImVec2(outerContentBox.Max - ImVec2(0, IMGUI_EX_NODE_FOOTER_HEIGHT)))
        ),
        leftPins(
            ImFloor(ImVec2(outerContentBox.Min.x,outerContentBox.Min.y+IMGUI_EX_NODE_HEADER_HEIGHT)),
            ImFloor(ImVec2(outerContentBox.Min.x,outerContentBox.Max.y-IMGUI_EX_NODE_FOOTER_HEIGHT)),
            0),
        rightPins(
            ImFloor(ImVec2(outerContentBox.Max.x,outerContentBox.Min.y+IMGUI_EX_NODE_HEADER_HEIGHT)),
            ImFloor(ImVec2(outerContentBox.Max.x,outerContentBox.Max.y-IMGUI_EX_NODE_FOOTER_HEIGHT)),
            0),
        scale(_scale),
        pinsFlags(ImGuiExNodePinsFlags_None)
    {
    }
};

struct ofxVPLinkData{ // VP stuff should not be in here... rename (?)
    int         _fromObjectID;
    int         _fromPinID;
    int         _linkID;
    std::string _linkLabel;
    ImVec2      _toPinPosition;
};

struct NodeConnectData{ // VP stuff should not be in here... (?)
    int connectType; // 1 connect, 2 disconnect, 3 re-connect
    int linkID;
    int fromObjectID;
    int fromOutletPinID;
    int toObjectID;
    int toInletPinID;
};

struct NodeLinkData {
    //std::string toPinUID, fromPinUID; // needed ?
    ImVec2 toPinPos, fromPinPos;
    std::string linkLabel;
    ImU32 linkColor;
};

struct BezierCurve {
    // the curve control points
    ImVec2 p0, p1, p2, p3;
};

struct LinkBezierData {
    BezierCurve bezier;
    int num_segments;
};


struct NodeCanvas {

    // Setup a drawing canvas space
    // Uses ImGui available space except if over-ridden with SetNextWindowPos and Size.
    bool Begin(const char* _id );

    // Must be called only when Begin() returned true.
    void End();

    // Draws the frame border
    void DrawFrameBorder(const bool& _drawOnForeground=true) const;

    // Draw Child windows (aka Nodes) on the canvas.
    // position and size may change be updated after function call.
    bool BeginNode( const char* _id, std::string _name, ImVec2& _pos, ImVec2& _size, const int& _numLeftPins, const int& _numRightPins, const bool& _canResize=true, const bool& _reduceNodeFrame=false );
    void EndNode();

    // Adds an inlet and sets its position on screen so you can do more graphic stuff with it.
    // Always call EndNodePins, only draw when it returns true.
    //void BeginNodePins( const int& _numPins, const ImGuiExNodePinsFlags& _pinFlags = ImGuiExNodePinsFlags_Left );
    //void EndNodePins();
    NodeConnectData AddNodePin(const int nodeID, const int pinID, const char* _label, ImVec2& _pinPosition, std::vector<ofxVPLinkData>& _linksData, std::string _type, bool _connected, const ImU32& _color, const ImGuiExNodePinsFlags& _pinFlag  );
    ImGuiExNodePinResponse AddNodePin( const char* _dragDropIdentifier, const char* _pinLabel, ImVec2& _pinPosition, const char* _linkLabel, const int& _linkTypeId, const ImU32& _pinColor, bool _pinIsConnected, const ImGuiExNodePinsFlags_& _pinFlag );
    ImGuiExNodeLinkActionFlags_ AddLink(const ImVec2& _fromPos, const ImVec2& _toPos, const ImU32& _color, const char* _label);

    // To extend the menu
    bool BeginNodeMenu();
    void EndNodeMenu();

    // To draw node content
    // Returns true if the view can be drawn
    bool BeginNodeContent( const ImGuiExNodeView& _renderingView=ImGuiExNodeView_Any );
    void EndNodeContent();

    // Menu actions
    // helper func. Otherwise you can access GetNodeData.menuActions
    bool doNodeMenuAction( const ImGuiExNodeMenuActionFlags& _menuItem=ImGuiExNodeMenuActionFlags_None );

    // For now you have to use an external / custom translation engine to navigate space.
    // Todo: It will be nice to have ImGui handle user interaction.
    void SetTransform(const ImVec2& _origin, float _scale);
    //void SetDisplayRect(const ImRect& _rect);

    // Query GUI if any nodes are hovered
    bool isAnyNodeHovered() const {
        //IM_ASSERT(isDrawingCanvas == true);  // dont call while drawing !
        return isAnyCanvasNodeHovered;
    }

    // Returns current view data.
    const NodeCanvasView& GetCanvasView() const {
        IM_ASSERT( isDrawingCanvas == true ); // Only between BeginNode() and EndNode()
        return canvasView;
    }
    // Returns origin of the view.
    const ImVec2& GetCanvasTranslation() const { return canvasView.translation; }

    // Returns scale of the view.
    float GetCanvasScale() const { return canvasView.scale; }

    // Returns data about the current node.
    // Useful inside: scale, newName, scaleName, etc.
    const NodeLayoutData& GetNodeData() const {
        IM_ASSERT( isDrawingNode == true ); // Use only between BeginNode() and EndNode()
        return curNodeData;
    }

    // Returns nodeDrawList
    ImDrawList* getNodeDrawList() const {
        IM_ASSERT(nodeDrawList != nullptr);
        return nodeDrawList;
    }

    // Returns selected nodes
    //std::vector<char*> getSelectedNodes(){ return selectedNodes; }

    // Returns selected links
    //std::vector<std::uintptr_t> getSelectedLinks(){ return selectedLinks; }

private:
//    void pushNodeWorkRect();
//    void popNodeWorkRect();
//    ImRect canvasWorkRectBackup;

    // state management bools
    bool isDrawingCanvas = false;
    bool isDrawingNode = false;
    bool canDrawNode = false;
    bool isDrawingMenu = false;
    bool isDrawingContent = false;
    bool isAnyCanvasNodeHovered = false;

    // State data
    NodeLayoutData curNodeData;
    NodeCanvasView  canvasView;
    ImDrawList* canvasDrawList = nullptr;
    ImDrawList* nodeDrawList = nullptr;

    // Patch Control data
    std::vector< char* > selectedNodes; // for group actions (copy, duplicate, delete) -- TO IMPLEMENT
    std::vector< std::uintptr_t > selectedLinks; // for delete links (one or multiple) -- IMPLEMENTED
    //std::vector< std::uintptr_t > selectedLinksToDelete;
    //std::string activePin;
    //std::string activePinType;

    NodeLinkData activeLink;
    std::string activeLinkSourcePinUID;
    //ImGuiExNodePinsFlags_ activeLinkSourcePinFlag;

};

} // namespace ImGuiEx

# endif // __IMGUI_EX_NODECANVAS_H__
