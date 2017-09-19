
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
        download_date = 'https://raw.githubusercontent.com/HowardHinnant/date/v2.2/date.h'
        download_tz = 'https://raw.githubusercontent.com/HowardHinnant/date/master/tz.h'
        download_tz_private = 'https://raw.githubusercontent.com/HowardHinnant/date/master/tz_private.h'
        download_tz_cpp = 'https://raw.githubusercontent.com/HowardHinnant/date/master/tz.cpp'

        download(download_date, 'date.h')
        download(download_tz, 'tz.h')
        download(download_tz_private, 'tz_private.h')
        download(download_tz_cpp, 'tz.cpp')

        check_sha256('date.h', '1b1883cb3aa05b288efddc5299ef7e15864fb354752241cf3bd1c16fbcc088b9')
        check_sha256('tz.h', 'b7e5c5ee242dbda36af22014536e2c7b06608f353a68264c75fd69df16e02f37')
        check_sha256('tz_private.h', '1789bc010f1b775695a6d4a967935623216940b60b279625ce608bdfbb36e0a5')
        check_sha256('tz.cpp', '6198e2cad92aa4262fa4109fb1fef11cb4fb9fac0f68cb4776a5babeb3cca370')

    def build(self):
        return  # do nothing - header only

    def package(self):
        self.copy(pattern='date.h', dst='include/date')
        self.copy(pattern='tz.h', dst='include/date')
        self.copy(pattern='tz_private.h', dst='include/date')
        self.copy(pattern='tz.cpp', dst='src/date')

    def package_id(self):
        self.info.header_only()