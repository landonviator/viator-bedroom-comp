# Bedroom Comp MkII

### Purpose

The purpose of this project is to provide a high-quality compressor plugin that offers enhanced compression functionality, including the knee parameter and VCA vs Opto compression models. This plugin serves as a foundational component of a larger paid compressor/limiter plugin that I intend to release at a modest price. The comprehensive package will include presets (which users can share with each other), MIDI mapping, oversampling, and other functions.

### What's inside?

This repo includes:

- [viatordsp JUCE User Module](https://github.com/landonviator/viatordsp)
- [Compressor DSP class](https://github.com/landonviator/viatordsp/blob/main/viator_modules/viator_dsp/Dynamics/Compressor.h) with attack, release, threshold, ratio, hpf, and knee parameters
- [Projucer Project](https://github.com/landonviator/viator-bedroom-comp/blob/main/viator-bedroom-comp/viator-bedroom-comp.jucer) built on top of the compressor dsp class

### How to download a build

You can get a build of Bedroom Comp MkII either from my [Gumroad](https://viatordsp.gumroad.com/l/sbnuyp) post or by downloading a build artifact from the repo's GitHub actions run.
From the [main code page](https://github.com/landonviator/viator-bedroom-comp) navigate to the _Actions_ tab, click the latest green workflow run, then grab the appropraite build from the _Articats_ section as either Mac AU, Mac VST3, or Windows VST3.

### Knee Parameter

My interest in nonlinear functions and their role in audio processing has been constant since completing my PhD. While my work focused on using chaotic equations to generate audio signals and modulate parameters in real-time, I've taken a different approach for this project. I aimed to create a unique and impactful knee parameter for Bedroom Comp. I experimented with various trigonometric functions until I achieved a distinctive and appealing knee curve. The result is not a typical knee response, which was intentional. Below, you'll find curves measured in PluginDoctor that illustrate the nonlinearity among the knee, ratio, and threshold. Although labeled "soft" and "hard" knees, the "soft" knee is anything but typical. :wink:

#### Hard Knee:

![Hard Knee](https://github.com/landonviator/viator-bedroom-comp/blob/main/hard-knee.png)

#### Soft Knee:

![Soft Knee](https://github.com/landonviator/viator-bedroom-comp/blob/main/soft-knee.png)

As you can observe, the knee parameter behaves distinctly from the usual compressor knee. Its unique punch contributes to enhanced articulation and excitement in audio.

## Contributing

Contributions to this open-source project are not only welcome but also encouraged. Both programmers and non-programmers can contribute in various ways:

#### Testing

The simplest way to contribute is by using the plugin in any way you like! All software has its share of bugs and glitches. Increased usage of the plugin will expedite the discovery and resolution of bugs. Different DAWs and hosts may exhibit varied behaviors, leading to different types of bugs. Additionally, considering potential use in non-DAW software, such as Elgato WaveLink, introduces additional considerations.

#### Plugin Development

If you're interested in contributing to the plugin's development, that's fantastic! Start by exploring the issues page. If you encounter no existing bugs and wish to introduce new features, fine-tune the DSP, or propose any other enhancements, feel free to submit a pull request (PR), which will be reviewed promptly.

## Support

If you like my work and would like to support me creating more audio applications, check out my [Patreon](https://www.patreon.com/ViatorDSP) where you can donate and download all of my current plugins! I also have a [GumRoad](https://viatordsp.gumroad.com/?_gl=1*18tqfoy*_ga*MTg2MjcxNDgyNS4xNjg5OTI3NDE3*_ga_6LJN6D94N6*MTY5MjM5NjQ1Ni4xODguMS4xNjkyMzk2NTExLjAuMC4w) store with my most recent plugins.

### References

The compressor class is mainly based on Eric Tarr's description in his book [Hack Audio](https://www.hackaudio.com/), where I added extra features like the highpass filter in the detection circuit and the weird, nonlinear knee.

## License

MIT License

Copyright (c) 2023 Landon Viator

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
