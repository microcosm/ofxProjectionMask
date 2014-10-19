ofxProjectionMask
=================
ofxProjectionMask is an addon which allows you to mask out areas of the real world onto which to project any light pattern you like.

![A screenshot of the mask designer UI](screenshot.png)

Unlike projection mapping, this is not about creating the illusion that a light surface is 'mapped onto' a physical object; instead this addon simply prevents the light from 'bleeding' outside of the mask.

In other words, this addon separates out the masking from the mapping, and only does the former without doing the latter. You can of course, still pre-transform your patterns in code if you want to achieve traditional projection mapping.

How does it work?
-----------------
There is a design UI allowing you to slice out a shape with your mouse, representing some physical object within view of your projector. At the same time you can draw() anything you like into a pattern class that you will create, based on a template included in the addon.

The addon has full instructions and samples in the example project, along with information about running fullscreen/dualscreen.

Project dependencies
--------------------
- [ofxTriangle](https://github.com/obviousjim/ofxTriangle) to build renderable triangles out of the points in your mask
- [ofxXmlSettings](http://www.openframeworks.cc/documentation/ofxXmlSettings/ofxXmlSettings.html) to store masks as you draw them - it's part of the openFrameworks core
- Tested against [openFrameworks 0.8.4](http://openframeworks.cc/download/)