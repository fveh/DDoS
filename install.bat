@echo off
echo Installing Network Last Tool dependencies...

:: Install WinPcap
curl -L -o winpcap.exe https://www.winpcap.org/install/bin/WinPcap_4_1_3.exe
start /wait winpcap.exe /S
del winpcap.exe

:: Install OpenSSL
curl -L -o openssl.exe https://slproweb.com/download/Win32OpenSSL-1_1_1w.exe
start /wait openssl.exe /VERYSILENT /SP- /SUPPRESSMSGBOXES /NORESTART
del openssl.exe

:: Set environment variables
setx OPENSSL_CONF "C:\Program Files (x86)\OpenSSL-Win32\bin\openssl.cfg"
setx PATH "%PATH%;C:\Program Files (x86)\OpenSSL-Win32\bin"

:: Install Windows SDK (if needed)
:: curl -L -o sdksetup.exe https://go.microsoft.com/fwlink/p/?linkid=2120843
:: start /wait sdksetup.exe /features + /quiet

echo Compiling Network Last Tool...
cl /EHsc /I "." /I "C:\Program Files (x86)\OpenSSL-Win32\include" ^
   main.cpp attacks\volume.cpp attacks\protocol.cpp ^
   attacks\application.cpp attacks\amplification.cpp ^
   obfuscation.cpp c2.cpp utils.cpp ^
   /link /LIBPATH:"C:\Program Files (x86)\OpenSSL-Win32\lib" ^
   libssl.lib libcrypto.lib ws2_32.lib iphlpapi.lib

echo Installation complete!
echo Run nltool.exe to start the Network Last Tool
pause
