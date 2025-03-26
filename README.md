This project is a simplified example of what my project structure currently looks
like. It shows that the built-in unit testing feature mixed with multiple configurations
does not work in a seamless way.

To generate the configuration files and build folders, please run 
"ESP-IDF: Select Configuration...", then "ESP-IDF: Set Espressif Device Target".

To generate the unity app as intended, run 
"ESP-IDF: Unit Test: Install ESP-IDF Python Dependencies...", then run
"ESP-IDF: Unit Test: Build and Flash Unit Testing App...". At this point,
the build should fail for lack of configuration files in the testing app. If
the files are directly added and the command re-run, the build should succeed,
however running unit tests through the VSCode "testing" tab will result in
errors.