#!/bin/bash
docker run -ti -v $(pwd):/shared -w /shared dolfinx/dolfinx
