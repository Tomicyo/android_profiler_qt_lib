set PROTOC="C:\Program Files\gRPC\bin\protoc.exe"

%PROTOC% --cpp_out=../cpp cpu.proto
%PROTOC% --grpc_out=../cpp --plugin=protoc-gen-grpc=E:\Github\grpc\build_kaleido3d\Release\grpc_cpp_plugin.exe cpu.proto

%PROTOC% --cpp_out=../cpp agent_service.proto
%PROTOC% --grpc_out=../cpp --plugin=protoc-gen-grpc=E:\Github\grpc\build_kaleido3d\Release\grpc_cpp_plugin.exe agent_service.proto

%PROTOC% --cpp_out=../cpp profiler_service.proto
%PROTOC% --grpc_out=../cpp --plugin=protoc-gen-grpc=E:\Github\grpc\build_kaleido3d\Release\grpc_cpp_plugin.exe profiler_service.proto

%PROTOC% --cpp_out=../cpp profiler.proto
%PROTOC% --grpc_out=../cpp --plugin=protoc-gen-grpc=E:\Github\grpc\build_kaleido3d\Release\grpc_cpp_plugin.exe profiler.proto

%PROTOC% --cpp_out=../cpp io.proto
%PROTOC% --grpc_out=../cpp --plugin=protoc-gen-grpc=E:\Github\grpc\build_kaleido3d\Release\grpc_cpp_plugin.exe io.proto

%PROTOC% --cpp_out=../cpp graphics.proto
%PROTOC% --grpc_out=../cpp --plugin=protoc-gen-grpc=E:\Github\grpc\build_kaleido3d\Release\grpc_cpp_plugin.exe graphics.proto

%PROTOC% --cpp_out=../cpp memory.proto
%PROTOC% --grpc_out=../cpp --plugin=protoc-gen-grpc=E:\Github\grpc\build_kaleido3d\Release\grpc_cpp_plugin.exe memory.proto