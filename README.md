# Srenderer

sRenderer is a software rendering program. All computation happens in CPU, no GPU involved. Which means no graphic libraries like OpenGL and Vulkan are Used. The only third library  used is SFML, which creates a window for us. Everything was built from scratch, including matrix computation, model loading, perspective projection, and shading.

There are two parts of this project:

- source code
- detailed documentation explaining everything you need to implement it (WIP)

<table>
  <tr>
    <td><center><img src="doc/assets/head.gif" width="200"></center></td>
    <td><center><img src="doc/assets/shark.gif" width="200"></center></td>
    <td><center><img src="doc/assets/tree.gif" width="200"></center></td>
  </tr>
</table>

# Features

- Pure software rendering
- No third libs used, except SFML to create window
- Matrix computation
- Model loading
- Perspective projection
- Shading
- Lighting
- Camera movement
- Detailed explanation of theory and implementation (WIP)

# Setup

- Platform
    - Linux
- Dependency
    - g++
    - make
- build and run
    
    ```bash
    cmake -B build
    cmake --build build
    ./build/sRender
    ```
    

# Project purpose

There are two purposes of this project.

- Check my understanding (by explaining it simply)
    
    Yes, Feynman Technique. I hope to uncover and fill gaps of my understanding.
    
    Honesty, this is my main purpose.
    
- Help your understanding
    
    I have learnt a lot of materials, some are very detailed but wordy, some with steep learning curve. I’m not a pro, but walked through all these by myself. Something that confuses you may also have confused me. I will provide the perspective of a muggle, try my best to clarify all these confusing complex stuffs. Hope it will be helpful to you.
    

# Attention

- You could use all these code for any purpose with no limitation.  But I think it’s not fit for production, since it’s basic and not optimized in performance.
- If you find anything not being explained clearly, or even wrong. Feel free to open issues. Your feedback will be very helpful. Very appreciate to it.
- English is not my mother tongue. Why it is written in English? Of course, for learning!! I apologize if it affect reading experience and understanding. Very appreciate if you would like to point out grammar or expression problems.
