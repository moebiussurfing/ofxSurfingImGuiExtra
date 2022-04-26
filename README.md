ofxSurfingImGuiExtra
=============================

## Overview

This is a _complementary repository_ with extra files and a kind of sandbox for testing **openFrameworks** projects using **ofxSurfingImGui**.  
**ofxSurfingImGui** is an **ImGui** toolkit for **openFrameworks** projects.  

Some **WIP** stuff like a Timeline/Sequencer or Node Patching TESTING projects.   

## WORK IN PROGRESS!

## INDEX

### 5. [TIMELINES AND SEQUENCERS](#5-timelines-and-sequencers-wip-1) [WIP]

### 6. [NODES PATCHING](#6-nodes-patching-wip-1) [WIP]

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