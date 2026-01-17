## VXT

### TODO

* Create EventSystem class in UFW.
* Create base Application class.
  * With EventSystem member.
  * With Window member.
  * With virtual configure function.
* ~~Create BatchRenderers~~.
* ~~.Create sprite batch renderer~~.
  * Fix
* ~~Create threaded CmdHandler class that reads from stdin and publishes events on the EventSystem.~~
* ~~Transform io::Keyboard and io::Mouse into static classes.~~
* ~~Turn GridLines into a component.~~
* ~~Add Constants.hpp~~
* ~~Add Camera::getPosition()~~
* ~~Add Camera add/sub/mul/div functions~~
* ~~Upgrade GLFW CONTEXT MAJOR VERSION to 4~~
* Create module based makefiles
* ~~A Create Transformation utility class/ns~~
* Should BatchRenderer implement Renderer?
* Add flush function to Renderer interface
* ~~Implement ELEMENT_BUFFER in Vertex2 Batch Renderer~~
* Clean up scene/entity/component
* Implement missing std functions
* Add draw circle function
* Add move operators for Entity class
* ~~Cross compile for Windows~~
* Move builder classes into one file (Builder.hpp)

### Set location of core dump

sudo sysctl -w kernel.core_pattern=/tmp/core-%e.%p.%h.%t

### Notes to self

-Wl,--subsystem,windows

_POSIX_C_SOURCE >= 200112L

COMPILE.cpp = \$(CXX) \$(CXXFLAGS) \$(CPPFLAGS) \$(TARGET_ARCH) -c

LINK.cpp = \$(CXX) \$(CXXFLAGS) \$(CPPFLAGS) \$(LDFLAGS) \$(TARGET_ARCH)

<code>
@-mkdir -p $(@D)<br>
@set -e; rm -f $@; \<br>
$(CXX) -MM $(CPPFLAGS) $(INCLUDES) $< > $@.$$$$; \<br>
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \<br>
rm -f $@.$$$$
</code>
