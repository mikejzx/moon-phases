#ifndef MOON_ASCII_H
#define MOON_ASCII_H

static const char *MOON_PHASE_ART[MOON_PHASE_COUNT] =
{
// New Moon
[NEW_MOON] = R"(
   _..._
 .'     '.
/         \
|         |
\         /
 '._   _.'
    ```
)",
// Waxing Crescent
[WAXING_CRESCENT] = R"(
   _..._
   `'-.-'.
       \--\
       |--|
;.____.'--/
 '._---_.'
    ```
)",
// First Quarter
[FIRST_QUARTER] = R"(
      ._
     |--'.
    /-----\
   |------|
  /-------/
  '_---_.'
    ```
)",
// Waxing Gibbous
[WAXING_GIBBOUS] = R"(
    ..._
   /----'.
  /-------\
  |-------|
  \-------/
   \---_.'
    ```
)",
// Full Moon
[FULL_MOON] = R"(
   _..._
 .'-----'.
/---------\
|---------|
\---------/
 '._---_.'
    ```
)",
// Waning Gibbous
[WANING_GIBBOUS] = R"(
   _...
 .'----\
/-------\
|-------|
\-------/
 '._---/
    ```
)",
// Last Quarter
[THIRD_QUARTER] = R"(
   _.
 .'--|
/-----\
|------|
\-------\
 '._---_'
    ```
)",
// Waning Crescent
[WANING_CRESCENT] = R"(
   _..._
 .'-.-'`
/--/
|--|
\--'.____.;
 '._---_.'
    ```
)"
};

#endif
