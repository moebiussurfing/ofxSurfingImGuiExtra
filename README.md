ofxSurfingImGuiExtra
=============================

## Overview

This is a _complementary repository_ with extra files, complementary docs and a kind of sandbox for testing **openFrameworks** projects using [ofxSurfingImGui](https://github.com/moebiussurfing/ofxSurfingImGui).  

**ofxSurfingImGui** is an **ImGui** toolkit for **openFrameworks** projects. 

Most stuff stills in **WIP** / **alpha state**. For example _Timeline/Sequencer_ or _Node Patching_ **TESTING PROJECTS**.  

More Info [README_DEV](/README_DEV.md).  

Usefull 3rd party Imgui widgets:  
[imgui/wiki/Useful-Extensions](https://github.com/ocornut/imgui/wiki/Useful-Extensions#image-manipulation)  

![GIFS](https://github.com/moebiussurfing/ofxSurfingImGuiExtra/blob/279ee0fc0614100a8393e751b6e6c955669a0dcb/readme_media/gif/README.md)  
[SCREENSHOTS](https://github.com/moebiussurfing/ofxSurfingImGuiExtra/blob/279ee0fc0614100a8393e751b6e6c955669a0dcb/readme_media/image/README.md)  

<BR>

## WORK IN PROGRESS!


## INDEX

### 1. [WIDGETS](#1-widgets-1)

### 2. [LAYOUT](#2-layout-1)

### 3. [STYLES](#3-styles-1)

### 4. [LAYOUTS & DOCKING](4-layouts--docking-wip-1) [WIP]


<BR>

## 1. WIDGETS

Shows **ofParameter** helpers with full/half/third/quarter width Buttons, Toggles, DearWidgets, Range Sliders, Bezier Curve, Spinner/Progress Indicators, and **ofxImGui** standard parameters.  

<details>
  <summary>1_1_Widgets_DearWidgets</summary>
  <p>

Includes Range Sliders with **ofParameters**, responsive Button/Toggles and the AWESOME [DearWidgets](https://github.com/soufianekhiat/DearWidgets) from **@soufianekhiat**.  
![image](/readme_media/image/1_1_Widgets_DearWidgets.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_2_Widgets_Curve</summary>
  <p>

Includes Bezier Curves and usable timed Tween/Easing functions.  
![image](/readme_media/image/1_2_Widgets_Curve.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_3_Widgets_Spinner</summary>
  <p>

Includes waiting and progress spinners.  
![gif](/readme_media/gif/1_3_Widgets_Spinner.gif?raw=true "gif")  
  </p>
</details>

<details>
  <summary>1_4_Widgets_Surfing</summary>
  <p>

Includes a **matrix button clicker selector** linked to an **ofParameter<int>** (aka preset index), small tooltips, spin clicker, and the awesome gradient engine from [@galloscript](https://twitter.com/galloscript) from his [Github Gist](https://gist.github.com/galloscript/8a5d179e432e062550972afcd1ecf112).  
![image](/readme_media/image/1_4_Widgets_Surfing.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_5_FileBrowser</summary>
  <p>

![image](/readme_media/image/1_5_FileBrowser.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_8_Knobs</summary>
  <p>

![image](/readme_media/image/1_8_Knobs.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 2. LAYOUT

Speed up **ofxImGui** instantiation (auto draw, viewport mode, fonts...), windows, and layouts.  
Includes **ofParameter** helpers, widget sizes, and extra widgets.  
_Notice that below at point **3. TYPES ENGINE**, there's a better NEW API!_ 

<details>
  <summary>Example Code</summary>
  <p>

  ![image](/readme_media/image/2_1_2_Layout_Basic.PNG?raw=true "image")  

ofApp.h

```.cpp
#include "ofxSurfingImGui.h"

ofxSurfingGui ui;

ofParameter<bool> bGui{ "Show Gui", true };

ofParameter<bool> bEnable{ "Enable", true };
ofParameter<bool> b1{ "b1", false };
ofParameter<bool> b2{ "b2", false };
ofParameter<bool> b3{ "b3", false };
```

ofApp.cpp

```.c++
void ofApp::setup() 
{ 
    ui.setup(); 

    // Instantiates and configures all the required ofxImGui stuff inside:
    // Font, theme, autodraw, layout store/recall, multi context/instances, ofParams Helpers and other customizations.
}

void ofApp::draw() 
{ 
    ui.Begin();
    if (bGui) // -> This param makes the close button functional
    {
        ui.BeginWindow("Window", (bool *)&bGui.get(), ImGuiWindowFlags_None);
        {
            ofxImGuiSurfing::AddToggleRoundedButton(bEnable);
            if (bEnable)
            {
                // Precalculate common widgets sizes to fit current window, "to be responsive".
                float _w1 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
                float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // 2 widgets half width
                float _w3 = ofxImGuiSurfing::getWidgetsWidth(3); // 3 widgets third width
                float _w4 = ofxImGuiSurfing::getWidgetsWidth(4); // 4 widgets quarter width
                float _h = ofxImGuiSurfing::getWidgetsHeightRelative(); // one unit height relative to ImGui theme

                //-

                /* Draw RAW ImGui or SurfingWidgets with ofParameters */

                // One widget full with and theme height. The callback is handled by the param listeners.
                ofxImGuiSurfing::AddBigToggle(b1); 

                // Two widgets same line/row with the 50% of window panel width 
                if (ofxImGuiSurfing::AddBigButton(b2, _w2, _h)) {
                  // This acts as callback. 
                  // No parameter listener required.
                }
                ImGui::SameLine();
                if (ofxImGuiSurfing::AddBigButton(b3, _w2, _h)) {
                  // This acts as callback. 
                  // No parameter listener required.
                }

                // Or using raw ImGui
                // Three widgets and fit width in one line
                if (ImGui::Button("START", ImVec2(_w3, _h))) {}
                ImGui::SameLine();
                if (ImGui::Button("STOP", ImVec2(_w3, _h))) {}
                ImGui::SameLine();
                if (ImGui::Button("REPLAY", ImVec2(_w3, _h))) {}
            }
        }
        ui.EndWindow();
    }
    ui.End();
}
```
</p>
</details>

<details>
  <summary>2_1_Layout_Basic</summary>
  <p>

![image](/readme_media/image/2_1_Layout_Basic.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>2_0_Layout_ofParamaters</summary>
  <p>

Includes **ofParameter** and **ofParameterGroup** helpers and customize how groups are presented: collapsed/expanded, hidden header, **ImGui::Tree/ImGui::TreeEx** ...etc.  
[BROKEN]  
![gif](/readme_media/gif/2_0_Layout_ofParamaters.gif?raw=true "gif")  
  </p>
</details>

<details>
  <summary>2_4_Layout_ThemeEditor</summary>
  <p>

This is a helper for tweaking your Themes: testings sizes, layout, and colors, and alternate fonts.  

Notice that you need to export the newly modified theme code through the clipboard and paste it to a new function/theme manually.  
There's not an automatic-fully-functional, save preset/load theme designer!  
![image](/readme_media/image/2_4_Layout_ThemeEditor.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 3. STYLES

One step forward for **ofHelpers**:  

* Fast **ofParameter**s widgets layout: responsive-auto_fit width, height, amount items per row, and different styles for the same types or even repeated parameters with different styles.  

* Also **ofParameterGroup** and their inside **ofParameters**, can be customized too with different **ImGui::Tree** settings, collapsed and nested.  

<details>
  <summary>Vertical and Horizontal Sliders</summary>
  <p>

![image](/readme_media/image/1_Widgets_Sliders.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>Grouped Vertical and Horizontal Sliders</summary>
  <p>

![image](/readme_media/image/1_Widgets_Sliders2.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>Nested Styled Groups</summary>
  <p>

![image](/readme_media/image/4_0_0_Layout_TypesEngine.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>Layout Engine</summary>
  <p>

![image](/readme_media/image/4_0_1_Layout_TypesEngine.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 4. LAYOUTS & DOCKING [WIP]

Examples to improve the layout of Docking Spaces. 

* Learn to split docking spaces by code, or using mouse control by the user.
* Docking helpers. **Engine Manager** to create layout presets.
<details>
  <summary>3_0_Layout_Docking2</summary>
  <p>

#### LAYOUT PRESETS ENGINE

* Fast adding of windows to the **Gui Manager**.
* Auto populates **Control Panels** to handle layout presets.
* Cute workflow for Management.
* You can add extra parameters to the presets too. 

![gif](/readme_media/gif/3_0_Layout_Docking2.gif?raw=true "gif")  
  </p>
</details>

<details>
  <summary>3_0_Layout_Docking3</summary>
  <p>

This example shows how to populate many ImGui windows from different scopes on the same viewport.  
Uses different approaches: from ofApp, from an add-on/class, or with Surfing Layout tools as ui.  
Also useful to check viewport modes, docking merging windows or auto draw modes.  

![image](/readme_media/image/3_0_Layout_Docking3.PNG?raw=true "png")  
  </p>
</details>

<BR>
<BR>

## EXTRA WIP STUFF INDEX

### 1. [MISCELLANEOUS](#1-miscellaneous-wip-1) [WIP]

### 2. [TIMELINES AND SEQUENCERS](#2-timelines-and-sequencers-wip-1) [WIP]

### 3. [NODES PATCHING](#3-nodes-patching-wip-1) [WIP]

<BR>
<BR>

## 1. MISCELLANEOUS [WIP]

<details>
  <summary>3_1_Layout_ImTools1</summary>
  <p>

Uses [ImTools](https://github.com/aiekick/ImTools) from **@aiekick**: "_ It's a class for manage docking panes in an easy way, display (panes, menu, pane dialog), load/save, auto layout, etc..._". **WIP** porting to use in my oF projects.  

An alternative to my Docking Layout Engine but without presets and with more development required.  
Nice to learn about ImGui Docking.  

![image](/readme_media/image/3_1_Layout_ImTools1.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 2. TIMELINES AND SEQUENCERS [WIP]

These are TESTING projects trying to build an operative but very basic timeline, to run very simple animations:  

* A kind of note on/off or clip start/end behavior.
* A curve editor for float variable automation. 

<details>
  <summary>4_1_ImSequencer</summary>
  <p>

Using [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)  
Still very raw yet, not functional: I need to [finish](https://github.com/CedricGuillemet/ImGuizmo/issues/185) the engine to read the values when frames are playing.  
![image](/readme_media/image/4_1_ImSequencer.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_3_Sequentity [BROKEN]</summary>
  <p>
  
Using [Sequentity](https://github.com/alanjfs/sequentity). It's being hard to port because of some dependencies...
  </p>
</details>

<BR>

## 3. NODES PATCHING [WIP]

These are testing [projects](https://github.com/ocornut/imgui/issues/306) with nodes/graph/patching.  
My target is to build a simple engine to patch between **ofParameters**.  
**For example**: _A simple patch-bay to route some **ofParameters** from an audio analyzer to the render scene **ofParameters**._   

<details>
  <summary>5_1_ImNodes_Nelarius</summary>
  <p>

Using [Nelarius/imnodes](https://github.com/Nelarius/imnodes)  
![image](/readme_media/image/5_1_ImNodes_Nelarius.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_4_ImNodes_rokups</summary>
  <p>

Using [rokups/ImNodes](https://github.com/rokups/ImNodes)  
![image](/readme_media/image/5_4_ImNodes_rokups.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_5_ImNodes_thedmd</summary>
  <p>

Using [thedmd/imgui-node-editor](https://github.com/thedmd/imgui-node-editor)  
![image](/readme_media/image/5_5_ImNodes_thedmd.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_5_2_ImNodes_thedmd-PatchBay</summary>
  <p>

[**WIP**] Using [ofxPatchbayParams](https://github.com/moebiussurfing/ofxPatchbayParams)  
![image](/readme_media/image/5_5_2_ImNodes_thedmd-PatchBay.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>6_7_DaanMosaic3</summary>
  <p>

Example code by [@Daandelange](https://github.com/Daandelange). Using [ofxVisualProgramming stuff](https://github.com/d3cod3/ofxVisualProgramming)  
![image](/readme_media/image/6_7_DaanMosaic3.PNG?raw=true "image")  
  </p>
</details>

5_5_ImNodes_thedmd-Blueprints [BROKEN]  
5_6_ImNodes-Graph-ImGuizmo [BROKEN]  

<BR>

## Dependencies
[ofxSurfingImGui](https://github.com/moebiussurfing/ofxSurfingImGui)  
[ofxImGui](https://github.com/Daandelange/ofxImGui/tree/develop) / AWESOME FORK from @**Daandelange**  
[ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers) / For examples only  
[ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) / For examples only  

## Tested Systems
- **Windows10** / **VS2017** / **OF ~0.11**

#### Thanks
_All source snippets from other authors are linked into header files. Thanks!_

#### License
**MIT License**

## Author
An addon by **@moebiusSurfing**  
*( ManuMolina ) 2021-2023*  
