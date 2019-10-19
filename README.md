<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Common Template Project](#common-template-project)
  - [About the project](#about-the-project)
  - [Why we use LD_PRELOAD](#why-we-use-ld_preload)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Common Template Project

## About the project

This repository records how we implement the hijack part of CUDA driver API.

## Why we use LD_PRELOAD

There are multiple ways to achieve hajicking CUDA driver APIs. One is using `LD_PRELOAD` while others inlcude replacing `libcuda.so` with `hijack.so`.

The second approach requires a complete implemtnation of all CUDA driver APIs, hijacked or not. For those non-hijacked APIs, at least a wrapper is neceessary. Otherwise, the implemtation of the function is missing.

With the second approach, when launching containers, we need to use docker images implanted with the hijacked shared library, which is not optimal if we would like to use this approach on a platform open to the users with their own images.

Under the consideration of `LD_PRELOAD`, a platform only needs to mount the hijacked shared library from each host (Node) onto the container if Nvidia GPU(s) is/are used as well as specifying the environment variable of `LD_PRELOAD`.

