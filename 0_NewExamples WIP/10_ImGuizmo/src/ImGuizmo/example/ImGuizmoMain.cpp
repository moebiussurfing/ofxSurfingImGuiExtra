#pragma once


#define USE_ONLY_GIZMOS//disables all below

//#define USE_Sequencer
//#define USE_GraphEditor
//#define USE_ZoomSlider




// https://github.com/CedricGuillemet/ImGuizmo
// v 1.89 WIP
//
// The MIT License(MIT)
//
// Copyright(c) 2021 Cedric Guillemet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"

#include "ImGuizmo.h"
#include "ImSequencer.h"
#include "ImZoomSlider.h"
#include "ImCurveEdit.h"
#include "GraphEditor.h"
#include <math.h>
#include <vector>
#include <algorithm>

static bool useWindow = true;
static int gizmoCount = 4;
static float camDistance = 8.f;
static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);

static float objectMatrix[4][16] = {
  { 1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f },

  { 1.f, 0.f, 0.f, 0.f,
  0.f, 1.f, 0.f, 0.f,
  0.f, 0.f, 1.f, 0.f,
  2.f, 0.f, 0.f, 1.f },

  { 1.f, 0.f, 0.f, 0.f,
  0.f, 1.f, 0.f, 0.f,
  0.f, 0.f, 1.f, 0.f,
  2.f, 0.f, 2.f, 1.f },

  { 1.f, 0.f, 0.f, 0.f,
  0.f, 1.f, 0.f, 0.f,
  0.f, 0.f, 1.f, 0.f,
  0.f, 0.f, 2.f, 1.f }
};

static const float identityMatrix[16] =
{ 1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f };

static void Frustum(float left, float right, float bottom, float top, float znear, float zfar, float* m16)
{
   float temp, temp2, temp3, temp4;
   temp = 2.0f * znear;
   temp2 = right - left;
   temp3 = top - bottom;
   temp4 = zfar - znear;
   m16[0] = temp / temp2;
   m16[1] = 0.0;
   m16[2] = 0.0;
   m16[3] = 0.0;
   m16[4] = 0.0;
   m16[5] = temp / temp3;
   m16[6] = 0.0;
   m16[7] = 0.0;
   m16[8] = (right + left) / temp2;
   m16[9] = (top + bottom) / temp3;
   m16[10] = (-zfar - znear) / temp4;
   m16[11] = -1.0f;
   m16[12] = 0.0;
   m16[13] = 0.0;
   m16[14] = (-temp * zfar) / temp4;
   m16[15] = 0.0;
}

static void Perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar, float* m16)
{
   float ymax, xmax;
   ymax = znear * tanf(fovyInDegrees * 3.141592f / 180.0f);
   xmax = ymax * aspectRatio;
   Frustum(-xmax, xmax, -ymax, ymax, znear, zfar, m16);
}

static void Cross(const float* a, const float* b, float* r)
{
   r[0] = a[1] * b[2] - a[2] * b[1];
   r[1] = a[2] * b[0] - a[0] * b[2];
   r[2] = a[0] * b[1] - a[1] * b[0];
}

static float Dot(const float* a, const float* b)
{
   return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

static void Normalize(const float* a, float* r)
{
   float il = 1.f / (sqrtf(Dot(a, a)) + FLT_EPSILON);
   r[0] = a[0] * il;
   r[1] = a[1] * il;
   r[2] = a[2] * il;
}

static void LookAt(const float* eye, const float* at, const float* up, float* m16)
{
   float X[3], Y[3], Z[3], tmp[3];

   tmp[0] = eye[0] - at[0];
   tmp[1] = eye[1] - at[1];
   tmp[2] = eye[2] - at[2];
   Normalize(tmp, Z);
   Normalize(up, Y);

   Cross(Y, Z, tmp);
   Normalize(tmp, X);

   Cross(Z, X, tmp);
   Normalize(tmp, Y);

   m16[0] = X[0];
   m16[1] = Y[0];
   m16[2] = Z[0];
   m16[3] = 0.0f;
   m16[4] = X[1];
   m16[5] = Y[1];
   m16[6] = Z[1];
   m16[7] = 0.0f;
   m16[8] = X[2];
   m16[9] = Y[2];
   m16[10] = Z[2];
   m16[11] = 0.0f;
   m16[12] = -Dot(X, eye);
   m16[13] = -Dot(Y, eye);
   m16[14] = -Dot(Z, eye);
   m16[15] = 1.0f;
}

static void OrthoGraphic(const float l, float r, float b, const float t, float zn, const float zf, float* m16)
{
   m16[0] = 2 / (r - l);
   m16[1] = 0.0f;
   m16[2] = 0.0f;
   m16[3] = 0.0f;
   m16[4] = 0.0f;
   m16[5] = 2 / (t - b);
   m16[6] = 0.0f;
   m16[7] = 0.0f;
   m16[8] = 0.0f;
   m16[9] = 0.0f;
   m16[10] = 1.0f / (zf - zn);
   m16[11] = 0.0f;
   m16[12] = (l + r) / (l - r);
   m16[13] = (t + b) / (b - t);
   m16[14] = zn / (zn - zf);
   m16[15] = 1.0f;
}

static inline void rotationY(const float angle, float* m16)
{
   float c = cosf(angle);
   float s = sinf(angle);

   m16[0] = c;
   m16[1] = 0.0f;
   m16[2] = -s;
   m16[3] = 0.0f;
   m16[4] = 0.0f;
   m16[5] = 1.f;
   m16[6] = 0.0f;
   m16[7] = 0.0f;
   m16[8] = s;
   m16[9] = 0.0f;
   m16[10] = c;
   m16[11] = 0.0f;
   m16[12] = 0.f;
   m16[13] = 0.f;
   m16[14] = 0.f;
   m16[15] = 1.0f;
}

static void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition)
{
   static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
   static bool useSnap = false;
   static float snap[3] = { 1.f, 1.f, 1.f };
   static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
   static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
   static bool boundSizing = false;
   static bool boundSizingSnap = false;

   if (editTransformDecomposition)
   {
      if (ImGui::IsKeyPressed(ImGuiKey_T))
         mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
      if (ImGui::IsKeyPressed(ImGuiKey_E))
         mCurrentGizmoOperation = ImGuizmo::ROTATE;
      if (ImGui::IsKeyPressed(ImGuiKey_R)) // r Key
         mCurrentGizmoOperation = ImGuizmo::SCALE;
      if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
         mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
      ImGui::SameLine();
      if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
         mCurrentGizmoOperation = ImGuizmo::ROTATE;
      ImGui::SameLine();
      if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
         mCurrentGizmoOperation = ImGuizmo::SCALE;
      if (ImGui::RadioButton("Universal", mCurrentGizmoOperation == ImGuizmo::UNIVERSAL))
         mCurrentGizmoOperation = ImGuizmo::UNIVERSAL;
      float matrixTranslation[3], matrixRotation[3], matrixScale[3];
      ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
      ImGui::InputFloat3("Tr", matrixTranslation);
      ImGui::InputFloat3("Rt", matrixRotation);
      ImGui::InputFloat3("Sc", matrixScale);
      ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

      if (mCurrentGizmoOperation != ImGuizmo::SCALE)
      {
         if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
            mCurrentGizmoMode = ImGuizmo::LOCAL;
         ImGui::SameLine();
         if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
            mCurrentGizmoMode = ImGuizmo::WORLD;
      }
      if (ImGui::IsKeyPressed(ImGuiKey_S))
         useSnap = !useSnap;
      ImGui::Checkbox("##UseSnap", &useSnap);
      ImGui::SameLine();

      switch (mCurrentGizmoOperation)
      {
      case ImGuizmo::TRANSLATE:
         ImGui::InputFloat3("Snap", &snap[0]);
         break;
      case ImGuizmo::ROTATE:
         ImGui::InputFloat("Angle Snap", &snap[0]);
         break;
      case ImGuizmo::SCALE:
         ImGui::InputFloat("Scale Snap", &snap[0]);
         break;
      }
      ImGui::Checkbox("Bound Sizing", &boundSizing);
      if (boundSizing)
      {
         ImGui::PushID(3);
         ImGui::Checkbox("##BoundSizing", &boundSizingSnap);
         ImGui::SameLine();
         ImGui::InputFloat3("Snap", boundsSnap);
         ImGui::PopID();
      }
   }

   ImGuiIO& io = ImGui::GetIO();
   float viewManipulateRight = io.DisplaySize.x;
   float viewManipulateTop = 0;
   static ImGuiWindowFlags gizmoWindowFlags = 0;
   if (useWindow)
   {
      ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_Appearing);
      ImGui::SetNextWindowPos(ImVec2(400,20), ImGuiCond_Appearing);
      ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor(0.35f, 0.3f, 0.3f));
      ImGui::Begin("Gizmo", 0, gizmoWindowFlags);
      ImGuizmo::SetDrawlist();
      float windowWidth = (float)ImGui::GetWindowWidth();
      float windowHeight = (float)ImGui::GetWindowHeight();
      ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
      viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
      viewManipulateTop = ImGui::GetWindowPos().y;
      ImGuiWindow* window = ImGui::GetCurrentWindow();
      gizmoWindowFlags = ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max) ? ImGuiWindowFlags_NoMove : 0;
   }
   else
   {
      ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
   }

   ImGuizmo::DrawGrid(cameraView, cameraProjection, identityMatrix, 100.f);

   ImGuizmo::DrawCubes(cameraView, cameraProjection, &objectMatrix[0][0], gizmoCount);
   
   ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

   ImGuizmo::ViewManipulate(cameraView, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);

   if (useWindow)
   {
      ImGui::End();
      ImGui::PopStyleColor(1);
   }
}

#ifdef USE_Sequencer
//
//
// ImSequencer interface
//
//
static const char* SequencerItemTypeNames[] = { "Camera","Music", "ScreenEffect", "FadeIn", "Animation" };

struct RampEdit : public ImCurveEdit::Delegate
{
   RampEdit()
   {
      mPts[0][0] = ImVec2(-10.f, 0);
      mPts[0][1] = ImVec2(20.f, 0.6f);
      mPts[0][2] = ImVec2(25.f, 0.2f);
      mPts[0][3] = ImVec2(70.f, 0.4f);
      mPts[0][4] = ImVec2(120.f, 1.f);
      mPointCount[0] = 5;

      mPts[1][0] = ImVec2(-50.f, 0.2f);
      mPts[1][1] = ImVec2(33.f, 0.7f);
      mPts[1][2] = ImVec2(80.f, 0.2f);
      mPts[1][3] = ImVec2(82.f, 0.8f);
      mPointCount[1] = 4;


      mPts[2][0] = ImVec2(40.f, 0);
      mPts[2][1] = ImVec2(60.f, 0.1f);
      mPts[2][2] = ImVec2(90.f, 0.82f);
      mPts[2][3] = ImVec2(150.f, 0.24f);
      mPts[2][4] = ImVec2(200.f, 0.34f);
      mPts[2][5] = ImVec2(250.f, 0.12f);
      mPointCount[2] = 6;
      mbVisible[0] = mbVisible[1] = mbVisible[2] = true;
      mMax = ImVec2(1.f, 1.f);
      mMin = ImVec2(0.f, 0.f);
   }
   size_t GetCurveCount()
   {
      return 3;
   }

   bool IsVisible(size_t curveIndex)
   {
      return mbVisible[curveIndex];
   }
   size_t GetPointCount(size_t curveIndex)
   {
      return mPointCount[curveIndex];
   }

   uint32_t GetCurveColor(size_t curveIndex)
   {
      uint32_t cols[] = { 0xFF0000FF, 0xFF00FF00, 0xFFFF0000 };
      return cols[curveIndex];
   }
   ImVec2* GetPoints(size_t curveIndex)
   {
      return mPts[curveIndex];
   }
   virtual ImCurveEdit::CurveType GetCurveType(size_t curveIndex) const { return ImCurveEdit::CurveSmooth; }
   virtual int EditPoint(size_t curveIndex, int pointIndex, ImVec2 value)
   {
      mPts[curveIndex][pointIndex] = ImVec2(value.x, value.y);
      SortValues(curveIndex);
      for (size_t i = 0; i < GetPointCount(curveIndex); i++)
      {
         if (mPts[curveIndex][i].x == value.x)
            return (int)i;
      }
      return pointIndex;
   }
   virtual void AddPoint(size_t curveIndex, ImVec2 value)
   {
      if (mPointCount[curveIndex] >= 8)
         return;
      mPts[curveIndex][mPointCount[curveIndex]++] = value;
      SortValues(curveIndex);
   }
   virtual ImVec2& GetMax() { return mMax; }
   virtual ImVec2& GetMin() { return mMin; }
   virtual unsigned int GetBackgroundColor() { return 0; }
   ImVec2 mPts[3][8];
   size_t mPointCount[3];
   bool mbVisible[3];
   ImVec2 mMin;
   ImVec2 mMax;
private:
   void SortValues(size_t curveIndex)
   {
      auto b = std::begin(mPts[curveIndex]);
      auto e = std::begin(mPts[curveIndex]) + GetPointCount(curveIndex);
      std::sort(b, e, [](ImVec2 a, ImVec2 b) { return a.x < b.x; });

   }
};

struct MySequence : public ImSequencer::SequenceInterface
{
   // interface with sequencer

   virtual int GetFrameMin() const {
      return mFrameMin;
   }
   virtual int GetFrameMax() const {
      return mFrameMax;
   }
   virtual int GetItemCount() const { return (int)myItems.size(); }

   virtual int GetItemTypeCount() const { return sizeof(SequencerItemTypeNames) / sizeof(char*); }
   virtual const char* GetItemTypeName(int typeIndex) const { return SequencerItemTypeNames[typeIndex]; }
   virtual const char* GetItemLabel(int index) const
   {
      static char tmps[512];
      snprintf(tmps, 512, "[%02d] %s", index, SequencerItemTypeNames[myItems[index].mType]);
      return tmps;
   }

   virtual void Get(int index, int** start, int** end, int* type, unsigned int* color)
   {
      MySequenceItem& item = myItems[index];
      if (color)
         *color = 0xFFAA8080; // same color for everyone, return color based on type
      if (start)
         *start = &item.mFrameStart;
      if (end)
         *end = &item.mFrameEnd;
      if (type)
         *type = item.mType;
   }
   virtual void Add(int type) { myItems.push_back(MySequenceItem{ type, 0, 10, false }); };
   virtual void Del(int index) { myItems.erase(myItems.begin() + index); }
   virtual void Duplicate(int index) { myItems.push_back(myItems[index]); }

   virtual size_t GetCustomHeight(int index) { return myItems[index].mExpanded ? 300 : 0; }

   // my datas
   MySequence() : mFrameMin(0), mFrameMax(0) {}
   int mFrameMin, mFrameMax;
   struct MySequenceItem
   {
      int mType;
      int mFrameStart, mFrameEnd;
      bool mExpanded;
   };
   std::vector<MySequenceItem> myItems;
   RampEdit rampEdit;

   virtual void DoubleClick(int index) {
      if (myItems[index].mExpanded)
      {
         myItems[index].mExpanded = false;
         return;
      }
      for (auto& item : myItems)
         item.mExpanded = false;
      myItems[index].mExpanded = !myItems[index].mExpanded;
   }

   virtual void CustomDraw(int index, ImDrawList* draw_list, const ImRect& rc, const ImRect& legendRect, const ImRect& clippingRect, const ImRect& legendClippingRect)
   {
      static const char* labels[] = { "Translation", "Rotation" , "Scale" };

      rampEdit.mMax = ImVec2(float(mFrameMax), 1.f);
      rampEdit.mMin = ImVec2(float(mFrameMin), 0.f);
      draw_list->PushClipRect(legendClippingRect.Min, legendClippingRect.Max, true);
      for (int i = 0; i < 3; i++)
      {
         ImVec2 pta(legendRect.Min.x + 30, legendRect.Min.y + i * 14.f);
         ImVec2 ptb(legendRect.Max.x, legendRect.Min.y + (i + 1) * 14.f);
         draw_list->AddText(pta, rampEdit.mbVisible[i] ? 0xFFFFFFFF : 0x80FFFFFF, labels[i]);
         if (ImRect(pta, ptb).Contains(ImGui::GetMousePos()) && ImGui::IsMouseClicked(0))
            rampEdit.mbVisible[i] = !rampEdit.mbVisible[i];
      }
      draw_list->PopClipRect();

      ImGui::SetCursorScreenPos(rc.Min);
      ImCurveEdit::Edit(rampEdit, rc.Max - rc.Min, 137 + index, &clippingRect);
   }

   virtual void CustomDrawCompact(int index, ImDrawList* draw_list, const ImRect& rc, const ImRect& clippingRect)
   {
      rampEdit.mMax = ImVec2(float(mFrameMax), 1.f);
      rampEdit.mMin = ImVec2(float(mFrameMin), 0.f);
      draw_list->PushClipRect(clippingRect.Min, clippingRect.Max, true);
      for (int i = 0; i < 3; i++)
      {
         for (int j = 0; j < rampEdit.mPointCount[i]; j++)
         {
            float p = rampEdit.mPts[i][j].x;
            if (p < myItems[index].mFrameStart || p > myItems[index].mFrameEnd)
               continue;
            float r = (p - mFrameMin) / float(mFrameMax - mFrameMin);
            float x = ImLerp(rc.Min.x, rc.Max.x, r);
            draw_list->AddLine(ImVec2(x, rc.Min.y + 6), ImVec2(x, rc.Max.y - 4), 0xAA000000, 4.f);
         }
      }
      draw_list->PopClipRect();
   }
};
#endif

#ifdef USE_GraphEditor
//
//
// GraphEditor interface
//
//

// Disabled as requires C++17/OF 12

template <typename T, std::size_t N>
struct Array
{
   T data[N];
   const size_t size() const { return N; }

   const T operator [] (size_t index) const { return data[index]; }
   operator T* () {
      T* p = new T[N];
      memcpy(p, data, sizeof(data));
      return p;
   }
};

template <typename T, typename ... U> Array(T, U...)->Array<T, 1 + sizeof...(U)>;

struct GraphEditorDelegate : public GraphEditor::Delegate
{
   bool AllowedLink(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) override
   {
      return true;
   }

   void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected) override
   {
      mNodes[nodeIndex].mSelected = selected;
   }

   void MoveSelectedNodes(const ImVec2 delta) override
   {
      for (auto& node : mNodes)
      {
         if (!node.mSelected)
         {
            continue;
         }
         node.x += delta.x;
         node.y += delta.y;
      }
   }

   virtual void RightClick(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex slotIndexInput, GraphEditor::SlotIndex slotIndexOutput) override
   {
   }

   void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex) override
   {
      mLinks.push_back({ inputNodeIndex, inputSlotIndex, outputNodeIndex, outputSlotIndex });
   }

   void DelLink(GraphEditor::LinkIndex linkIndex) override
   {
      mLinks.erase(mLinks.begin() + linkIndex);
   }

   void CustomDraw(ImDrawList* drawList, ImRect rectangle, GraphEditor::NodeIndex nodeIndex) override
   {
      drawList->AddLine(rectangle.Min, rectangle.Max, IM_COL32(0, 0, 0, 255));
      drawList->AddText(rectangle.Min, IM_COL32(255, 128, 64, 255), "Draw");
   }

   const size_t GetTemplateCount() override
   {
      return sizeof(mTemplates) / sizeof(GraphEditor::Template);
   }

   const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex index) override
   {
      return mTemplates[index];
   }

   const size_t GetNodeCount() override
   {
      return mNodes.size();
   }

   const GraphEditor::Node GetNode(GraphEditor::NodeIndex index) override
   {
      const auto& myNode = mNodes[index];
      return GraphEditor::Node
      {
          myNode.name,
          myNode.templateIndex,
          ImRect(ImVec2(myNode.x, myNode.y), ImVec2(myNode.x + 200, myNode.y + 200)),
          myNode.mSelected
      };
   }

   const size_t GetLinkCount() override
   {
      return mLinks.size();
   }

   const GraphEditor::Link GetLink(GraphEditor::LinkIndex index) override
   {
      return mLinks[index];
   }

   // Graph datas
   static const inline GraphEditor::Template mTemplates[] = {
       {
           IM_COL32(160, 160, 180, 255),
           IM_COL32(100, 100, 140, 255),
           IM_COL32(110, 110, 150, 255),
           1,
           Array{"MyInput"},
           nullptr,
           2,
           Array{"MyOutput0", "MyOuput1"},
           nullptr
       },

       {
           IM_COL32(180, 160, 160, 255),
           IM_COL32(140, 100, 100, 255),
           IM_COL32(150, 110, 110, 255),
           3,
           nullptr,
           Array{ IM_COL32(200,100,100,255), IM_COL32(100,200,100,255), IM_COL32(100,100,200,255) },
           1,
           Array{"MyOutput0"},
           Array{ IM_COL32(200,200,200,255)}
       }
   };

   struct Node
   {
      const char* name;
      GraphEditor::TemplateIndex templateIndex;
      float x, y;
      bool mSelected;
   };

   std::vector<Node> mNodes = {
       {
           "My Node 0",
           0,
           0, 0,
           false
       },

       {
           "My Node 1",
           0,
           400, 0,
           false
       },

       {
           "My Node 2",
           1,
           400, 400,
           false
       }
   };

   std::vector<GraphEditor::Link> mLinks = { {0, 0, 1, 0} };
};

#endif

