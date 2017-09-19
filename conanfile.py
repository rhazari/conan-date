import os, shutil
from conans import ConanFile, CMake
from conans.tools import download, check_sha256, unzip

class HowardHinnantDate(ConanFile):
    name = 'date'
    version = '2.2.0'
    description = 'A date and time library based on the C++11/14/17 <chrono> header'
    url = 'https://github.com/rhazari/conan-date'
    license = 'https://github.com/rhazari/date/blob/{!s}-cmake/LICENSE.txt'.format(version)
    settings = 'os', 'compiler', 'arch', 'build_type'
    options = { 'tzdata_dir': 'ANY' }
    default_options = 'tzdata_dir=None'
    exports_sources = 'CMakeLists.txt', 'tzdata*'
    generators = 'cmake'

    @property
    def _archive_dirname(self):
        return 'date-{!s}-cmake'.format(self.version)

    def _get_build_dir(self):
        return os.getcwd()

    def _run_cmake(self):
        extra_defs = {}
        cmake = CMake(self, parallel=True)
        cmake.definitions['INSTALL'] = '.' #os.path.abspath(self._get_build_dir())
        cmake.configure(defs=extra_defs, build_dir=self._get_build_dir(), source_dir=self.conanfile_directory)
        return cmake

    def source(self):
        download_url = 'https://github.com/rhazari/date/archive/{!s}-cmake.zip'.format(self.version)
        download(download_url, 'date.zip')
        check_sha256('date.zip','a5dffa60d2743808c39b511a392e390901fc3eee6d3592c623e6b471695c043c')
        unzip('date.zip')
        os.unlink('date.zip')
        os.rename(self._archive_dirname, 'date')

    def build(self):
        cmake = self._run_cmake()    # rerun cmake
        #cmake.build(build_dir=self._get_build_dir())
        cmake.build()

    def package(self):
        self.copy(pattern='*.h', dst='include/date')

    def package_info(self):
        # TODO: change me to not affect consuming projects
        self.cpp_info.defines.append('INSTALL={!s}'.format(self.options.tzdata_dir))

    def package_id(self):
        self.info.header_only()