import os, shutil
from conans import ConanFile, CMake
from conans.tools import download, check_sha256, unzip

class HowardHinnantDate(ConanFile):
    name = 'date'
    version = '2.2.2'
    description = 'A date and time library based on the C++11/14/17 <chrono> header'
    url = 'https://github.com/rhazari/conan-date'
    license = 'https://github.com/rhazari/date/blob/{!s}-cmake/LICENSE.txt'.format(version)
    settings = 'os', 'compiler', 'arch', 'build_type'
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
        cmake.configure(defs=extra_defs, build_dir=self._get_build_dir(), source_dir=self.conanfile_directory)
        return cmake

    def source(self):
        download_url = 'https://github.com/rhazari/date/archive/{!s}-cmake.zip'.format(self.version)
        download(download_url, 'date.zip')
        check_sha256('date.zip','db2c684ee6d1a52a5046b5a1c152be277b0464b72feb36885d68eb7301a71982')
        unzip('date.zip')
        os.unlink('date.zip')
        os.rename(self._archive_dirname, 'date')

    def build(self):
        cmake = self._run_cmake()    # rerun cmake
        cmake.build()

    def package(self):
        self.copy(pattern='*.h', dst='include/')
        self.copy(pattern='*.cpp', dst='src/')

    def package_id(self):
        self.info.header_only()
