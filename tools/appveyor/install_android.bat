pushd %~dp0
cd /
appveyor DownloadFile http://dl.google.com/android/android-sdk_r24.3.4-windows.zip
7z x android-sdk_r24.3.4-windows.zip > nul
appveyor DownloadFile https://dl.google.com/android/repository/android-ndk-r15c-windows-x86_64.zip
7z x android-ndk-r15c-windows-x86_64.zip
appveyor DownloadFile https://dl.google.com/android/repository/cmake-3.6.4111459-windows-x86_64.zip
7z x cmake-3.6.4111459-windows-x86_64.zip -oC:\android-sdk-windows\cmake\3.6.4111459
@rem echo y | C:\android-sdk-windows\tools\android.bat update sdk --no-ui --all --filter android-23
@rem echo y | C:\android-sdk-windows\tools\android.bat update sdk --no-ui --all --filter platform-tools
@rem echo y | C:\android-sdk-windows\tools\android.bat update sdk --no-ui --all --filter tools
@rem echo y | C:\android-sdk-windows\tools\android.bat update sdk --no-ui --all --filter build-tools-23.0.2
@rem echo y | C:\android-sdk-windows\tools\android.bat update sdk --no-ui --all --filter extra-google-m2repository
@rem echo y | C:\android-sdk-windows\tools\android.bat update sdk --no-ui --all --filter extra-android-m2repository
popd