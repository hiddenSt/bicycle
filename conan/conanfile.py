import conan.errors
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class BicycleRecipe(ConanFile):
    name = 'bicycle'
    version = '1.0.0'
    license = 'MIT License'
    author = 'Viktor Repin'
    url = 'https://github.com/hiddenSt/bicycle'
    description = 'TODO'
    topics = ('concurrency', '')

    settings = 'os', 'compiler', 'build_type', 'arch'
    options = {'shared': [True, False], 'fPIC': [True, False]}
    default_options = {'shared': False, 'fPIC': True}
    exports_sources = ''

    def config_options(self):
        if self.settings.os == 'Windows':
            raise conan.errors.ConanInvalidConfiguration('Windows is not supported')

    def layout(self):
        cmake_layout(self)

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ['bicycle']
