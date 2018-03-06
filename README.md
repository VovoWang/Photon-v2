## What is Photon-v2?
Photon-v2 is a rendering engine made out of my personal interest in computer graphics. A rendering engine is what takes geometrical descriptions and material properties of a 3-D scene as input, and outputs a 2-D image of that scene from a specific point of view. In layman's terms, it is like taking a photograph, except the scene and the camera are both computer simulated. Different from its previous version, Photon, which was written entirely in Java, Photon-v2 utilizes the powerful C++14 for the rendering core and builds a GUI on top of it with Java via JNI. This project is currently in development and more features are expected to come. <br />

## Features
* **Integration (rendering method)**
  * backward path tracing
  * ~~backward light tracing (next event estimation)~~
  * ~~MIS'ed backward tracing (path + light)~~
  * ~~light/particle tracing~~

* **Material**
  * Lambertian diffuse
  * microfacet-based opaque & translucent model
  * ideal reflector & transmitter

* **Geometry**
  * sphere
  * rectangle
  * cuboid
  * triangle mesh
  * simple 2-D wave

* **Light**
  * area light

* **Texture**
  * texture with ordinary file formats (.jpg, .png, etc)
  * mathematical modifiers (add, multiply)

* **Misc.**
  * Blender addon for scene creation
  * easy-to-write custom scene description language
  * simple GUI for rendering

## Roadmap
* **Near Future (in 1 ~ 3 months)**
  * stabilize core engine structure
  * fully support common materials
  * basic addon for Blender
  * distributed rendering system
  * binary version of Photon-SDL

* **Mid-term (in 3 ~ 6 months)**
  * material node editor & parser
  * able to convert Cycles material for use in Photon
  * a complete Blender addon

* **Future Works (~1 year or later)**
  * documentation & website
  * render a short CG film using Photon

## Build
Photon-v2 is being developed with cross-platformity in mind, but Windows is the only platform that has been tested, for now. <br />

(building instructions will be added soon...) <br />

## Images Rendered by Photon-v2
| <a href="./gallery/028_sponza gold cups 12800spp.png"><img src="./gallery/028_sponza gold cups 12800spp.png" align="left" width="450" ></a> | <a href="./gallery/048_Arc Reactor (Iron Man) by kuhn0362 8000spp.png"><img src="./gallery/048_Arc Reactor (Iron Man) by kuhn0362 8000spp.png" align="left" width="450" ></a> |
| :---: | :---: |
| Gold Cups in Sponza | Arc Reactor (Iron Man) by "kuhn0362"|

| <a href="./gallery/044_scenery glass dragon 6000spp.png"><img src="./gallery/044_scenery glass dragon 6000spp.png" align="left" width="450" ></a> | <a href="./gallery/045_water dragon color light.png"><img src="./gallery/045_water dragon color light.png" align="left" width="450" ></a> |
| :---: | :---: |
| Scenery with Glass Dragon | Dragon in Fluid |

## Scene Description Language
The scene descripting language (SDL) designed by T.C. Chang can be stored into a text file (.p2 filename extension) and loaded by Photon-v2 for rendering. To create a scene, you can either open up a text file and start writing right away (visit folder "./scenes/" for reference) or install the Blender addon (in "./BlenderAddon/"), which contains a .p2 file exporter and a material editor currently.

## About the Author
Development Blog: http://tcchangs.blogspot.tw/ <br />
YouTube Channel:  https://www.youtube.com/channel/UCKdlogjqjuFsuv06wajp-2g <br />
Facebook Page:    https://www.facebook.com/tccthedeveloper/ <br />
E-mail:           r05922176@ntu.edu.tw <br />

If you use Photon in your research project, you are hightly encouraged to cite it using the following BibTeX template:

```latex.bib
@misc { Photon,
	Author = {Tzu-Chieh Chang},
	Year   = {2016--2018},
	Title  = {Photon renderer},
	Note   = {https://github.com/TzuChieh/Photon-v2}
} 
```

Feel free to send me an e-mail for any questions or ideas about my project (= <br />
