# TinyRTC

TinyRTC is an Arduino library for using DS3231 RTC with AtTiny85.

Note that you need to use Spence Konde's ATTiny Core for these routines to work; otherwise you'll get errors such as:
```bash
error: 'PIN_USI_CL' was not declared in this scope
error: 'PIN_USI_SCL' was not declared in this scope
```
For more information about the ATTiny Core, take a look at [the repository](https://github.com/SpenceKonde/ATTinyCore).
Also, this library uses the TinyI2CMaster library. You can find the repository in [this link](https://github.com/technoblogy/tiny-i2c).

## License
[Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/)