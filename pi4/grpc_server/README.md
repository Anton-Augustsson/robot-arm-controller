
## Create compiler docker container
```bash
docker build -t grpc_server_build_env .
```

## Compile
```bash
docker run --rm --mount type=bind,source=${PWD},target=/src grpc_server_build_env bash -c "/src/compile.sh && /bin/bash"
```
