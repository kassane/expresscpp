from conans import ConanFile, CMake, tools
import subprocess


class ExpressCpp(ConanFile):
    name = "expresscpp"
    result = subprocess.run(['git', 'describe'], stdout=subprocess.PIPE)
    version = result.stdout.decode('utf-8')
    license = "MIT"
    url = "https://gitlab.com/expresscpp/expresscpp"
    description = "same as expressjs for nodejs but for C++"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = ["cmake", "cmake_find_package", "cmake_paths"]
    exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "include/*", "conanfile.txt"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def requirements(self):
        self.requires.add("gtest/1.8.1@bincrafters/stable")
        self.requires.add("boost/1.71.0@conan/stable")
        self.requires.add("jsonformoderncpp/3.6.1@vthiery/stable")
        self.requires.add("fmt/5.3.0@bincrafters/stable")
        self.requires.add("magic_enum/0.6.2@neargye/stable")

    def package(self):
        self.copy("*.hpp", src=".")
        self.copy("*expresscpp.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["expresscpp"]