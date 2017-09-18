
from conans import ConanFile
from conans.tools import download, check_sha256

class HowardHinnantDate(ConanFile):
    name = 'date'
    version = '2.2.0'
    description = 'A date and time library based on the C++11/14/17 <chrono> header'
    url = 'https://github.com/rhazari/conan-date'
    license = 'https://github.com/HowardHinnant/date/blob/master/LICENSE.txt'
    settings = None

    def source(self):
        download_url = 'https://raw.githubusercontent.com/HowardHinnant/date/v2.2/date.h'
        download(download_url, 'date.h')
        check_sha256('date.h', '1b1883cb3aa05b288efddc5299ef7e15864fb354752241cf3bd1c16fbcc088b9')

    def build(self):
        return  # do nothing - header only

    def package(self):
        self.copy(pattern='date.h', dst='include/date')

    def package_id(self):
        self.info.header_only()