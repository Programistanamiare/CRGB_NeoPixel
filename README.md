# CRGB_NeoPixel v1.0.0

**CRGB_NeoPixel** is an **extension to the FastLED** library that adds new classes to facilitate the handling of multiple LED strips by applying overloading of the "[ ]" operator, both single and double, in the case of an array of LED strips. The FastLED library is included in the library so there is no need to download it additionally.

## Example

```cpp

  #include "../../CRGB_NeoPxiel.h"

  #define STRIP_NUM 3
  #define COLOR     0x00FF00


  // create 3 strips
  CRGB_buffer strips[STRIP_NUM] =
  {
    {10}, {20}, {15}
  };

  // create container for strips
  CRGB_Container container(strips, STRIP_NUM);

  void setup()
  {
    // in template argument set strip data pin.
    strips[0].setup<2>();
    strips[1].setup<3>();
    strips[2].setup<4>();
  }

  void loop()
  {

    // sequential switching on of the LED pixels in green.
    for (uint16_t i = 0; i < STRIP_NUM; ++i) {
      for (uint16_t j = 0; j < strips[i].lenght; ++j) {
        container[i][j] = COLOR;
        FastLED.show();
        delay(100);
      }
    }
    delay(2000);

    // sequential switching off of the LED pixels.
    for (uint16_t i = STRIP_NUM-1; i >= 0; --i) {
      for (uint16_t j = strips[i].lenght - 1; j >= 0; --j) {
        container[i][j] = 0;
        FastLED.show();
        delay(100);
      }
    }
    delay(2000);
  }

```

for this and other examples click <a href="https://github.com/Programistanamiare/CRGB_NeoPixel/tree/master/examples">here</a>.

## Documentation

### CRGB structures
<details>
<summary>Data structures used in classes.</summary>

A structure that stores information about the LED strip and pixel indices.

```cpp
  struct PixelPos 
  {
    uint16_t strip;
    uint16_t pixel;
  }
```

A structure that stores information about the connection point of two LED strips.

```cpp
  struct Connection2Strips
  {
    PixelPos first;
    PixelPos second;
  }
```

</details>

### CRGB_buffer
<details>
<summary>A class storing CRGB object array, and information about a LED strip.</summary>

Constructor<br>
@param **lenght** number of pixel in strip.

```cpp
  CRGB_buffer::CRGB_buffer(uint16_t lenght);
```

A template member function that sets the signal pin.<br>
@param **data_pin** data pin number.

```cpp
  template<uint8_t data_pin>
  void CRGB_buffer::setup();
```

Reloading the '[ ]' operator to manage a single pixel of the led strip.<br>
@param **index** pixel index,<br>
@return reference to CRGB pixel.

```cpp
  CRGB& CRGB_buffer::operator[](uint16_t index);
```

A member function that return number of pixels.

```cpp
  const uint16_t CRGB_buffer::lenght() const;
```

</details>

### CRGB_Container

<details>
<summary>A class storing <b>CRGB_buffer</b> objects.</summary>
---
Constructors:<br>

```cpp
  CRGB_Container::CRGB_Container();
```

@param **crgb_buffer_array** pointer to CRGB_buffer objects array,<br>
@param **array_size** CRGB_buffer array size.

```cpp
  CRGB_Container::CRGB_Container(CRGB_buffer* crgb_buffer_array, uint16_t array_size);
```
---
<br><br>
---
A member function that sets a pointer to the array of led strips and its length.<br>
@param **crgb_buffer_array** pointer to CRGB_buffer objects array,<br>
@param **array_size** CRGB_buffer array size.<br>
<br>
@attention **use of this function is mandatory when calling the default constructor. After all, no one defends creating an array of such objects. If you only use one instance of the CRGB_Container class, use the parameterized constructor of that class.**

```cpp
  void CRGB_Container::setCRGB_buffer(CRGB_buffer* crgb_buffer_array, uint16_t array_size);
```
---
<br><br>
---
A member function that return number of CRGB_buffer objects.

```cpp
  const uint16_t CRGB_Container::lenght() const;
```
---
<br><br>
---
A member function that return number of pixel in CRGB_buffer object.<br>
@param **index** CRGB_buffer index.<br>
@attention **If CRGB_buffer array has not been set this function always return 0.**

```cpp
  const uint16_t CRGB_Container::getStripLenght(const uint16_t& index) const;
```
---
<br><br>
---
Reloading the '[ ]' operator to manage the single CRGB_buffer LEDs strip.<br>
@param **index** index of CRGB_buffer.<br>
@return reference to CRGB_buffer object.
@attention **This member function is not protected against "index out of range" error. Be sure that you have given a pointer to an array of CRGB_buffer objects and that the index does not exceed the size of the given array.**

```cpp
  CRGB_buffer& CRGB_Container::operator[](const uint16_t& index);
```
---
<br><br>
---
Reloading the '[ ]' operator to manage the single CRGB_buffer LED pixel.<br>
@param **pos** structure that store information about indexes CRGB_buffer and pixel from this object.<br>
@return reference to CRGB object.<br>
@attention **This member function is not protected against "index out of range" error. Be sure that you have given a pointer to an array of CRGB_buffer objects and that the indexes does not exceed the size of the given array.**

```cpp
  CRGB& CRGB_Container::operator[](const PixelPos& pos);
```
---
</details>

### CRGB_Container_user (abstract class)

<details>
<summary>an abstract class that provides a constructor that takes a pointer to the <b>CRGB_Container</b> class, and a method to set it.</summary>

#### Constructors:<br>

---
Default constructor.<br>
@attention **When using this constructor, the <b>CRGB_Container_user::setContainer(CRGB_Container*)</b> member function should be used for the object to work properly.**

```cpp
  CRGB_Container_user::CRGB_Container_user();
```
---
<br><br>
---
A constructor that takes a pointer to a <b>CRGB_Container</b> object.<br>
@param **container** pointer to CRGB_Container object.

```cpp
  CRGB_Container_user::CRGB_Container_user(CRGB_Container* container);
```
---
<br><br>
A member function that takes a pointer to a <b>CRGB_Container</b> object.<br>
@param **container** pointer to CRGB_Container object.

```cpp
  void CRGB_Container_user::setContainer(CRGB_Container* container);
```
---

</details>
