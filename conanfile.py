
from conans import ConanFile
from conans.tools import download, check_sha256

class HowardHinnantDate(ConanFile):
    name = 'date'
    version = ''
    description = 'A date and time library based on the C++11/14/17 <chrono> header'
    url = 'https://github.com/rhazari/conan-date'
    license = 'https://github.com/HowardHinnant/date/blob/master/LICENSE.txt'
    settings = None

    def source(self):
        download_url = 'https://raw.githubusercontent.com/HowardHinnant/date/v2.2/date.h'
        download(download_url, 'date.h')
        check_sha256('date.h', 'a500c2a1ebee8e1a6bf524416e7c94ac71203cf715c5181714691b5206145db6')

    def build(self):
        return  # do nothing - header only

    def package(self):
        self.copy(pattern='date.h', dst='include/date')

    def package_id(self):
        self.info.header_only()