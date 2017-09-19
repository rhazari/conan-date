import os, shutil
from conans import ConanFile, CMake
from conans.tools import download, check_sha256, unzip

class HowardHinnantDate(ConanFile):
    name = 'date'
    version = '2.1.0'
    description = 'A date and time library based on the C++11/14/17 <chrono> header'
    url = 'https://github.com/rhazari/conan-date'
    license = 'https://github.com/HowardHinnant/date/blob/master/LICENSE.txt'
    settings = 'os', 'compiler', 'arch', 'build_type'

    @property
    def _archive_dirname(self):
        return 'date-{!s}-cmake'.format(self.version)

    def _get_build_dir(self):
        return os.path.join(os.getcwd(), 'date')

    def _run_cmake(self):
        extra_defs = {}
        cmake = CMake(self, parallel=True)
        cmake.configure(defs=extra_defs, build_dir=self._get_build_dir(), source_dir=self._get_build_dir())
        return cmake

    def source(self):
        download_url = 'https://github.com/rhazari/date/archive/2.1.0-cmake.zip'
        download(download_url, 'date.zip')
        check_sha256('date.zip','aeffe980f1d512305724f063ceb32683913f9319a1eed27788f1d6d8fd32a6ca')
        unzip('date.zip')
        os.unlink('date.zip')
        os.rename(self._archive_dirname, 'date')

    def build(self):
        cmake = self._run_cmake()    # rerun cmake
        cmake.build(build_dir=self._get_build_dir())

    def package(self):
        self.copy(pattern='*.h', dst='include/date')

    def package_id(self):
        self.info.header_only()