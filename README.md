This project is a simplified example of what my project structure currently looks
like. It shows that the built-in unit testing feature mixed with multiple configurations
does not work in a seamless way.

To generate the configuration files and build folders, please run 
"ESP-IDF: Select Configuration...", then "ESP-IDF: Set Espressif Device Target".

To generate the unity app as intended, run 
"ESP-IDF: Unit Test: Install ESP-IDF Python Dependencies...", then run
"ESP-IDF: Unit Test: Build and Flash Unit Testing App...". At this point,
the build should fail for lack of configuration files in the testing app. Specifically,

```
CMake Error at C:/Users/bapti/esp/v5.4/esp-idf/tools/cmake/project.cmake:645 (message):
  SDKCONFIG_DEFAULTS
  'C:/Users/bapti/Documents/Issue1478_Example/unity-app/configurations/sdkconfig.default2'
  does not exist.
Call Stack (most recent call first):
  CMakeLists.txt:13 (project)
```

If the configuration folders/files are directly added, the build directory for the 
configuration is deleted, and the command re-run, the build will succeed. Unfortunately,
the build is for the esp32 target instead of the target specified with the
"ESP-IDF: Set Espressif Device Target" command. 

```
 *  Executing task: C:\Users\bapti\.espressif\python_env\idf5.4_py3.11_env\Scripts\python.exe C:\Users\bapti\esp\v5.4\esp-idf\components\esptool_py\esptool\esptool.py -p COM8 -b 460800 --before default_reset --after hard_reset --chip esp32 write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 bootloader/bootloader.bin 0x10000 example_test_app.bin 0x8000 partition_table/partition-table.bin 

esptool.py v4.8.1
Serial port COM8
Connecting...

A fatal error occurred: This chip is ESP32-S3 not ESP32. Wrong --chip argument?
```

The app can be flashed onto an ESP32 though, which I am fortunate to have a copy of.
However, running unit tests through the VSCode "testing" tab will result in errors.
When running 'passingFunc', which should pass the test, results in:

```
======================================================================================================== test session starts ========================================================================================================
platform win32 -- Python 3.11.2, pytest-8.3.5, pluggy-1.5.0
rootdir: C:\Users\bapti\Documents\Issue1478_Example\unity-app
plugins: embedded-1.16.0, ignore-test-results-0.3.0, rerunfailures-15.0, timeout-2.3.1
collected 1 item

test_unit_case.py E

============================================================================================================== ERRORS =============================================================================================================== 
___________________________________________________________________________________________ ERROR at setup of test_unit_test[passesFunc] ____________________________________________________________________________________________ 

args = ()
kwargs = {'_fixture_classes_and_options': ClassCliOptions(classes={'app': <class 'pytest_embedded_idf.app.IdfApp'>, 'serial': <...app.IdfApp object at 0x0000016C4A299410>, 'msg_queue': <pytest_embedded.log.MessageQueue object at 0x0000016C4A27D190>}
_close_or_terminate = <function multi_dut_generator_fixture.<locals>.wrapper.<locals>._close_or_terminate at 0x0000016C4A28EFC0>, res = None

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        def _close_or_terminate(obj):
            if obj is None:
                del obj
                return
    
            try:
                if isinstance(obj, (subprocess.Popen, multiprocessing.process.BaseProcess)):
                    obj.terminate()
                    obj.kill()
                elif isinstance(obj, io.IOBase):
                    try:
                        obj.close()
                    except Exception as e:
                        logging.debug('file %s closed failed with error: %s', obj, str(e))
                else:
                    try:
                        obj.close()
                    except AttributeError:
                        try:
                            obj.terminate()
                        except AttributeError:
                            pass
                    except Exception as e:
                        logging.debug('Not properly caught object %s: %s', obj, str(e))
            except Exception as e:
                logging.debug('%s: %s', obj, str(e))
                return  # swallow up all error
            finally:
                referrers = gc.get_referrers(obj)
                for _referrer in referrers:
                    if isinstance(_referrer, list):
                        for _i, val in enumerate(_referrer):
                            if val is obj:
                                _referrer[_i] = None
                    elif isinstance(_referrer, dict):
                        for key, value in _referrer.items():
                            if value is obj:
                                _referrer[key] = None
                del obj

        if _COUNT == 1:
            res = None
            try:
>               res = func(*args, **kwargs)

..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded\plugin.py:514:
_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded\plugin.py:1137: in serial
    return serial_gn(**locals())
..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded\dut_factory.py:463: in serial_gn
    return cls(**_drop_none_kwargs(kwargs))
_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 

self = <pytest_embedded_idf.serial.IdfSerial object at 0x0000016C49F23BD0>, app = <pytest_embedded_idf.app.IdfApp object at 0x0000016C4A299410>, target = None, confirm_target_elf_sha256 = False, erase_nvs = False
kwargs = {'baud': 115200, 'esp_flash_force': False, 'esptool_baud': 921600, 'meta': Meta(logdir='C:\\Users\\bapti\\AppData\\Loc..._15-52-34-761717\\test_unit_test[passesFunc]', port_target_cache={}, port_app_cache={}, logfile_extension='.log'), ...}

    def __init__(
        self,
        app: IdfApp,
        target: Optional[str] = None,
        confirm_target_elf_sha256: bool = False,
        erase_nvs: bool = False,
        **kwargs,
    ) -> None:
        self.app = app
        self.confirm_target_elf_sha256 = confirm_target_elf_sha256
        self.erase_nvs = erase_nvs

        if not hasattr(self.app, 'target'):
>           raise ValueError(f"Idf app not parsable. Please check if it's valid: {self.app.binary_path}")
E           ValueError: Idf app not parsable. Please check if it's valid: None

..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded_idf\serial.py:37: ValueError
-------------------------------------------------------------------------------------------------------- Captured log setup --------------------------------------------------------------------------------------------------------- 
WARNING  root:app.py:108 config\sdkconfig.json doesn't exist. Skipping...
========================================================================================================= warnings summary ========================================================================================================== 
test_unit_case.py::test_unit_test[passesFunc]
  test_unit_case.py:22: PytestExperimentalApiWarning: record_xml_attribute is an experimental feature
    def test_unit_test(dut: Dut, test_name: str) -> None:

test_unit_case.py::test_unit_test[passesFunc]
  test_unit_case.py:22: PytestWarning: record_xml_attribute is incompatible with junit_family 'xunit2' (use 'legacy' or 'xunit1')
    def test_unit_test(dut: Dut, test_name: str) -> None:

-- Docs: https://docs.pytest.org/en/stable/how-to/capture-warnings.html
------------------------------------------------------------------------- generated xml file: C:\Users\bapti\Documents\Issue1478_Example\unity-app\test.xml ------------------------------------------------------------------------- 
=========================================================================================================== Failed Cases ============================================================================================================ 
============================================================================= you can use --ignore-result-files or --ignore-result-cases to ignore them ============================================================================= 
test_unit_case.py::test_unit_test[passesFunc]
====================================================================================================== short test summary info ======================================================================================================
ERROR test_unit_case.py::test_unit_test[passesFunc] - ValueError: Idf app not parsable. Please check if it's valid: None
=================================================================================================== 2 warnings, 1 error in 0.75s ==================================================================================================== 

 *  The terminal process "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -Command pytest --junitxml test.xml --skip-autoflash y --embedded-services esp,idf -s --test-name 'passesFunc'" terminated with exit code: 1.
```

The 'failsFunc' similarly fails, but in a way that is not expected:

```
======================================================================================================== test session starts ========================================================================================================
platform win32 -- Python 3.11.2, pytest-8.3.5, pluggy-1.5.0
rootdir: C:\Users\bapti\Documents\Issue1478_Example\unity-app
plugins: embedded-1.16.0, ignore-test-results-0.3.0, rerunfailures-15.0, timeout-2.3.1
collected 1 item

test_unit_case.py E

============================================================================================================== ERRORS =============================================================================================================== 
____________________________________________________________________________________________ ERROR at setup of test_unit_test[failsFunc] ____________________________________________________________________________________________ 

args = ()
kwargs = {'_fixture_classes_and_options': ClassCliOptions(classes={'app': <class 'pytest_embedded_idf.app.IdfApp'>, 'serial': <...app.IdfApp object at 0x00000190DC999B50>, 'msg_queue': <pytest_embedded.log.MessageQueue object at 0x00000190DC985B50>}
_close_or_terminate = <function multi_dut_generator_fixture.<locals>.wrapper.<locals>._close_or_terminate at 0x00000190DC98EA20>, res = None

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        def _close_or_terminate(obj):
            if obj is None:
                del obj
                return
    
            try:
                if isinstance(obj, (subprocess.Popen, multiprocessing.process.BaseProcess)):
                    obj.terminate()
                    obj.kill()
                elif isinstance(obj, io.IOBase):
                    try:
                        obj.close()
                    except Exception as e:
                        logging.debug('file %s closed failed with error: %s', obj, str(e))
                else:
                    try:
                        obj.close()
                    except AttributeError:
                        try:
                            obj.terminate()
                        except AttributeError:
                            pass
                    except Exception as e:
                        logging.debug('Not properly caught object %s: %s', obj, str(e))
            except Exception as e:
                logging.debug('%s: %s', obj, str(e))
                return  # swallow up all error
            finally:
                referrers = gc.get_referrers(obj)
                for _referrer in referrers:
                    if isinstance(_referrer, list):
                        for _i, val in enumerate(_referrer):
                            if val is obj:
                                _referrer[_i] = None
                    elif isinstance(_referrer, dict):
                        for key, value in _referrer.items():
                            if value is obj:
                                _referrer[key] = None
                del obj

        if _COUNT == 1:
            res = None
            try:
>               res = func(*args, **kwargs)

..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded\plugin.py:514:
_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded\plugin.py:1137: in serial
    return serial_gn(**locals())
..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded\dut_factory.py:463: in serial_gn
    return cls(**_drop_none_kwargs(kwargs))
_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 

self = <pytest_embedded_idf.serial.IdfSerial object at 0x00000190DBDBF290>, app = <pytest_embedded_idf.app.IdfApp object at 0x00000190DC999B50>, target = None, confirm_target_elf_sha256 = False, erase_nvs = False
kwargs = {'baud': 115200, 'esp_flash_force': False, 'esptool_baud': 921600, 'meta': Meta(logdir='C:\\Users\\bapti\\AppData\\Loc...6_15-53-21-625282\\test_unit_test[failsFunc]', port_target_cache={}, port_app_cache={}, logfile_extension='.log'), ...}

    def __init__(
        self,
        app: IdfApp,
        target: Optional[str] = None,
        confirm_target_elf_sha256: bool = False,
        erase_nvs: bool = False,
        **kwargs,
    ) -> None:
        self.app = app
        self.confirm_target_elf_sha256 = confirm_target_elf_sha256
        self.erase_nvs = erase_nvs

        if not hasattr(self.app, 'target'):
>           raise ValueError(f"Idf app not parsable. Please check if it's valid: {self.app.binary_path}")
E           ValueError: Idf app not parsable. Please check if it's valid: None

..\..\..\.espressif\python_env\idf5.4_py3.11_env\Lib\site-packages\pytest_embedded_idf\serial.py:37: ValueError
-------------------------------------------------------------------------------------------------------- Captured log setup --------------------------------------------------------------------------------------------------------- 
WARNING  root:app.py:108 config\sdkconfig.json doesn't exist. Skipping...
========================================================================================================= warnings summary ========================================================================================================== 
test_unit_case.py::test_unit_test[failsFunc]
  test_unit_case.py:22: PytestExperimentalApiWarning: record_xml_attribute is an experimental feature
    def test_unit_test(dut: Dut, test_name: str) -> None:

test_unit_case.py::test_unit_test[failsFunc]
  test_unit_case.py:22: PytestWarning: record_xml_attribute is incompatible with junit_family 'xunit2' (use 'legacy' or 'xunit1')
    def test_unit_test(dut: Dut, test_name: str) -> None:

-- Docs: https://docs.pytest.org/en/stable/how-to/capture-warnings.html
------------------------------------------------------------------------- generated xml file: C:\Users\bapti\Documents\Issue1478_Example\unity-app\test.xml ------------------------------------------------------------------------- 
=========================================================================================================== Failed Cases ============================================================================================================ 
============================================================================= you can use --ignore-result-files or --ignore-result-cases to ignore them ============================================================================= 
test_unit_case.py::test_unit_test[failsFunc]
====================================================================================================== short test summary info ====================================================================================================== 
ERROR test_unit_case.py::test_unit_test[failsFunc] - ValueError: Idf app not parsable. Please check if it's valid: None
=================================================================================================== 2 warnings, 1 error in 0.77s ==================================================================================================== 

 *  The terminal process "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -Command pytest --junitxml test.xml --skip-autoflash y --embedded-services esp,idf -s --test-name 'failsFunc'" terminated with exit code: 1. 
```
