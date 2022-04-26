ofxSurfingImGuiExtra
=============================

## Overview

This is a complementary repository with extra files and a kind of sandbox for testing **openFrameworks** projects using **ofxSurfingImGui**.  
**ofxSurfingImGui** is an **ImGui** toolkit for **openFrameworks** projects.  

Some **WIP** stuff like a Timeline/Sequencer or Node Patching TESTING projects.   

## WORK IN PROGRESS!

## INDEX

### 4. [DOCKING AND LAYOUT PRESETS ENGINE](#4-docking-and-layout-presets-engine-wip-1) [WIP]

### 5. [TIMELINES AND SEQUENCERS](#5-timelines-and-sequencers-wip-1) [WIP]

### 6. [NODES PATCHING](#6-nodes-patching-wip-1) [WIP]

## 4. DOCKING AND LAYOUT PRESETS ENGINE [WIP]

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

![image](/docs/3_0_Layout_Docking2.gif?raw=true "gif")  
  </p>
</details>

<details>
  <summary>3_0_Layout_Docking3</summary>
  <p>

This example shows how to populate many ImGui windows from different scopes on the same viewport.  
Uses different approaches: from ofApp, from an add-on/class, or with Surfing Layout tools as guiManager.  
Also useful to check viewport modes, docking merging windows or autodraw modes.  

![image](/docs/3_0_Layout_Docking3.PNG?raw=true "png")  
  </p>
</details>

<details>
  <summary>3_1_Layout_ImTools1</summary>
  <p>

Uses [ImTools](https://github.com/aiekick/ImTools) from **@aiekick**: "_ It's a class for manage docking panes in an easy way, display (panes, menu, pane dialog), load/save, auto layout, etc..._". **WIP** porting to use into my oF projects.  

An alternative to my Docking Layout Engine but without presets and with more development required.  
Nice to learn about ImGui Docking.  

![image](/docs/3_1_Layout_ImTools1.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 5. TIMELINES AND SEQUENCERS [WIP]

These are TESTING projects trying to build an operative but very basic timeline, to run very simple animations:  

* A kind of note on/off or clip start/end behavior.
* A curve editor for float variable automation. 

<details>
  <summary>4_1_ImSequencer</summary>
  <p>

Using [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)  
Still very raw yet, not functional: I need to [finish](https://github.com/CedricGuillemet/ImGuizmo/issues/185) the engine to read the values when frames are playing.  
![image](/docs/4_1_ImSequencer.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_3_Sequentity [BROKEN]</summary>
  <p>
  
Using [Sequentity](https://github.com/alanjfs/sequentity). It's being hard to port because of some dependencies...
  </p>
</details>

<BR>

## 6. NODES PATCHING [WIP]

These are testing [projects](https://github.com/ocornut/imgui/issues/306) with nodes/graph/patching.  
My target is to build a simple engine to patch between **ofParameters**.  
**For example**: _A simple patch-bay to route some **ofParameters** from an audio analyzer to the render scene **ofParameters**._   

<details>
  <summary>5_1_ImNodes_Nelarius</summary>
  <p>

Using [Nelarius/imnodes](https://github.com/Nelarius/imnodes)  
![image](/docs/5_1_ImNodes_Nelarius.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_4_ImNodes_rokups</summary>
  <p>

Using [rokups/ImNodes](https://github.com/rokups/ImNodes)  
![image](/docs/5_4_ImNodes_rokups.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_5_ImNodes_thedmd</summary>
  <p>

Using [thedmd/imgui-node-editor](https://github.com/thedmd/imgui-node-editor)  
![image](/docs/5_5_ImNodes_thedmd.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>5_5_2_ImNodes_thedmd-PatchBay</summary>
  <p>

[**WIP**] Using [ofxPatchbayParams](https://github.com/moebiussurfing/ofxPatchbayParams)  
![image](/docs/5_5_2_ImNodes_thedmd-PatchBay.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>6_7_DaanMosaic3</summary>
  <p>

Example code by [@Daandelange](https://github.com/Daandelange). Using [ofxVisualProgramming stuff](https://github.com/d3cod3/ofxVisualProgramming)  
![image](/docs/6_7_DaanMosaic3.PNG?raw=true "image")  
  </p>
</details>

5_5_ImNodes_thedmd-Blueprints [BROKEN]  
5_6_ImNodes-Graph-ImGuizmo [BROKEN]  

<BR>

## Dependencies
[ofxImGui](https://github.com/Daandelange/ofxImGui/) : AWESOME FORK from @**Daandelange**  
[ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)  
[ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) : For some examples only  

## Tested Systems
- **Windows10** / **VS2017** / **OF ~0.11**

## Author
An addon by **@moebiusSurfing**  
*( ManuMolina ) 2021-2022*  

#### Thanks
_All source snippets from other authors are linked into header files. Thanks!_

#### License
**MIT License**

<BR>

<details>
  <summary>Some Reference Links</summary>
  <p>

https://github.com/HankiDesign/awesome-dear-imgui -> Collected widgets  
https://github.com/soufianekhiat/DearWidgets -> Cute widgets already included  
https://github.com/yumataesu/ImGui_Widgets -> oF ready widgets  
https://github.com/aiekick/ImTools/tree/main/LayoutManager  
https://github.com/Organic-Code/ImTerm -> Interesting terminal to look into  
https://github.com/d3cod3/ofxVisualProgramming -> oF node patched system  
https://github.com/d3cod3/Mosaic -> oF node patched system  
https://github.com/mnesarco/imgui_sugar/blob/main/imgui_sugar.hpp -> macros  
https://github.com/njazz/AutomationCurveEditor  
https://github.com/leiradel/ImGuiAl  

  </p>
</details>