  . Test.cpp, which contains main(), is a sequence of unit tests corresponding to the different steps of the test.
  . Test uses two modules (cpp + hxx) called LoadBalancer and Provider

  . Program implemented on MacOs Big Sur 11.1 with Eclipse and gcc:

      gcc -v
      Configured with: --prefix=/Applications/Xcode-beta.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode-beta.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
      Apple clang version 12.0.0 (clang-1200.0.32.28)
      Target: x86_64-apple-darwin20.2.0
      Thread model: posix
      InstalledDir: /Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin

  . Build instructions:
       g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/LoadBalancer.d" -MT"src/LoadBalancer.o" -o "src/LoadBalancer.o" "../src/LoadBalancer.cpp"
       g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Provider.d" -MT"src/Provider.o" -o "src/Provider.o" "../src/Provider.cpp"
       g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/test.d" -MT"src/test.o" -o "src/test.o" "../src/test.cpp"
       g++  -o "test"  ./src/LoadBalancer.o ./src/Provider.o ./src/test.o   

    Run instructions:
        ./Debug/test > output.txt
        
    
