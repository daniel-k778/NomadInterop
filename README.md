# NomadInterop

NomadInterop is a **powerful and easy-to-use** wrapper for the [Nomad optimizer](https://www.gerad.ca/NOMAD/), designed to streamline the integration of Nomad's core functions into your C++ and C# projects. Unlike the original Nomad library, which primarily supports C++, NomadInterop allows developers to utilize the optimizer's capabilities in **both C++ and C#**, making it a **versatile tool for multi-language projects.**

- Integrate Nomad's optimization functions in both C++ and C# environments.
- Access Nomad's powerful optimization features with a straightforward and intuitive API.
- Efficient runtime and memory consumption.
- Fully open-source and available for modification to suit your specific needs.

## Installation

**Get the latest [binaries, modules and configuration files](https://github.com/daniel-k778/NomadInterop/releases/tag/v1.0) from the latest release.** Alternatively clone the repository and build from source.

### C++

**Include the necessary dlls and headers in your project:**
- nomad.dll
- sgtelib.dll
- nomadlibx64cpp.dll
- BaseEvaluator.hpp
- NomadCore.hpp
- Defines.hpp

### C#

**Include the necessary dlls in your project:**
- nomad.dll
- sgtelib.dll
- nomadlibx64cs.dll

## Examples

See [examples](./examples) for detailed examples on how to integrate NomadInterop into your C++ and C# applications.

## Documentation
For detailed documentation on how to use each function, refer to the [official NOMAD documentation](https://nomad-4-user-guide.readthedocs.io/en/latest/) or the [NOMAD user guide](./docs/user_guide.pdf).

## Contributing
If you have suggestions for improvements or have found bugs, feel free to open an issue.

## License
This project is licensed under the MIT License. See [LICENSE](./LICENSE) for more details.
