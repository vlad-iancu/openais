# Getting Started
```
git clone https://github.com/vlad-iancu/openais.git
cd openais/
mkdir Build/
cmake -DCMAKE_BUILD_TYPE="Debug" ..
make all -j{jobs}
```

### Create the first task
```
./Scripts/CreateTask.sh Example Periodic
cd Build
cmake -DCMAKE_BUILD_TYPE="Debug" ..
make
```
Now you have your first task located at `${PROJECT}/Build/Bin/ExampleTask`

```
export OPENAIS_CONFIG_DIR="${PROJECT}/Build/Config/"
cd Build
./Bin/ExampleTask
```

Now you should see
```
ExampleTask is running...
ExampleTask is running...
ExampleTask is running...
^C
```
