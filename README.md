# MetricsDiscoveryHelper

MetricsDiscoveryHelper is a runtime library that helps configure and collect
Intel GPU metrics using the [Intel&reg; Metrics Discovery
API](https://github.com/intel/metrics-discovery).  The intent is that this is a
fairly thin layer that:

- implements some of the common functionality requried to access the Intel&reg;
  MetricsDiscovery API,
- adds some abstractions that simplify use in real-time applications,
- provides an interface that can be implemented by Intel&reg; MetricsFramework,
- and has as low overhead as possible for use in real-time analysis scenarios.

Please see [CONTRIBUTING](CONTRIBUTING.md) for information on how to request
features, report issues, or contribute code changes.

## License

Copyright 2018 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## MetricsDiscovery API

[Intel&reg; Metrics Discovery API](https://github.com/intel/metrics-discovery)
is the Intel graphics driver's API providing access to GPU architecture
properties, metrics, and override controls.  Understanding these requires
knowledge of Intel GPU architecture as described in Intel's [Programmer's
Reference
Manuals](https://01.org/linuxgraphics/documentation/hardware-specification-prms)
and/or [Graphics Developer
Guides](https://software.intel.com/en-us/articles/intel-graphics-developers-guides).

See [metrics_discovery_helper.h](source/metrics_discovery_helper.h) for
documentation on how to use this library, as well as the following samples of
example usage:

| Example | Description |
| - | - |
| [samples/list_metrics](samples/list_metrics/list_metrics.cpp) | Enumerate all Global Symbols, Overrides, Concurrent Groups, Metric Sets, Metrics, and Information available on the system. |
| [samples/periodic_sample](samples/periodic_sample/periodic_sample.cpp) | Demonstrates sampling metrics at a periodic interval. |
| [samples/range_sample_dx11](samples/range_sample_dx11/range_sample_dx11.cpp) | Demonstrates sampling metrics around a range of DX11 commands. |

Metrics are organized into a hierarchy of "sets" within "concurrent groups".
Within each concurrent group, you can only activate a single metric set at a
time.  However, one metric set can be active from each concurrent group at the
same time.

Particular metrics are architecture specific, and may not be available on other
GPUs.

The following are example metrics from the "RenderBasic" metric set in the "OA"
concurrent group available on a Skylake (Gen9) GT2 GPU.  There are more metrics
available in other metric sets; use the `list_metrics` sample to list all the
metrics available on your system.

| Metric SymbolName | Description |
| - | - |
| GpuTime                          | Time elapsed on the GPU during the measurement. |
| GpuCoreClocks                    | The total number of GPU core clocks elapsed during the measurement. |
| AvgGpuCoreFrequencyMHz           | Average GPU Core Frequency in the measurement. |
| VsThreads                        | The total number of vertex shader hardware threads dispatched. |
| HsThreads                        | The total number of hull shader hardware threads dispatched. |
| DsThreads                        | The total number of domain shader hardware threads dispatched. |
| GsThreads                        | The total number of geometry shader hardware threads dispatched. |
| PsThreads                        | The total number of pixel shader hardware threads dispatched. |
| CsThreads                        | The total number of compute shader hardware threads dispatched. |
| GpuBusy                          | The percentage of time in which the GPU has been processing GPU commands. |
| EuActive                         | The percentage of time in which the Execution Units were actively processing. |
| EuStall                          | The percentage of time in which the Execution Units were stalled. |
| EuFpuBothActive                  | The percentage of time in which both EU FPU pipelines were actively processing. |
| VsFpu0Active                     | The percentage of time in which EU FPU0 pipeline was actively processing a vertex shader instruction. |
| VsFpu1Active                     | The percentage of time in which EU FPU1 pipeline was actively processing a vertex shader instruction. |
| VsSendActive                     | The percentage of time in which EU send pipeline was actively processing a vertex shader instruction. |
| PsFpu0Active                     | The percentage of time in which EU FPU0 pipeline was actively processing a pixel shader instruction. |
| PsFpu1Active                     | The percentage of time in which EU FPU1 pipeline was actively processing a pixel shader instruction. |
| PsSendActive                     | The percentage of time in which EU send pipeline was actively processing a pixel shader instruction. |
| PsEuBothFpuActive                | The percentage of time in which pixel shaders were processed actively on the both FPUs. |
| Sampler0Busy                     | The percentage of time in which Sampler 0 has been processing EU requests. |
| Sampler1Busy                     | The percentage of time in which Sampler 1 has been processing EU requests. |
| SamplersBusy                     | The percentage of time in which samplers have been processing EU requests. |
| Sampler0Bottleneck               | The percentage of time in which Sampler 0 has been slowing down the pipe when processing EU requests. |
| Sampler1Bottleneck               | The percentage of time in which Sampler 1 has been slowing down the pipe when processing EU requests. |
| RasterizedPixels                 | The total number of rasterized pixels. |
| HiDepthTestFails                 | The total number of pixels dropped on early hierarchical depth test. |
| EarlyDepthTestFails              | The total number of pixels dropped on early depth test. |
| SamplesKilledInPs                | The total number of samples or pixels dropped in pixel shaders. |
| PixelsFailingPostPsTests         | The total number of pixels dropped on post-PS alpha, stencil, or depth tests. |
| SamplesWritten                   | The total number of samples or pixels written to all render targets. |
| SamplesBlended                   | The total number of blended samples or pixels written to all render targets. |
| SamplerTexels                    | The total number of texels seen on input (with 2x2 accuracy) in all sampler units. |
| SamplerTexelMisses               | The total number of texels lookups (with 2x2 accuracy) that missed L1 sampler cache. |
| SamplerL1Misses                  | The total number of sampler cache misses in all LODs in all sampler units. |
| SlmBytesRead                     | The total number of GPU memory bytes read from shared local memory. |
| SlmBytesWritten                  | The total number of GPU memory bytes written into shared local memory. |
| ShaderMemoryAccesses             | The total number of shader memory accesses to L3. |
| ShaderAtomics                    | The total number of shader atomic memory accesses. |
| L3Lookups                        | The total number of L3 cache lookup accesses w/o IC. |
| L3Misses                         | The total number of L3 misses. |
| L3SamplerThroughput              | The total number of GPU memory bytes transferred between samplers and L3 caches. |
| L3ShaderThroughput               | The total number of GPU memory bytes transferred between shaders and L3 caches w/o URB. |
| ShaderBarriers                   | The total number of shader barrier messages. |
| GtiVfThroughput                  | The total number of GPU memory bytes transferred between 3D Pipeline (Command Dispatch, Input Assembly and Stream Output) and GTI. |
| GtiDepthThroughput               | The total number of GPU memory bytes transferred between depth caches and GTI. |
| GtiRccThroughput                 | The total number of GPU memory bytes transferred between render color caches and GTI. |
| GtiL3Throughput                  | The total number of GPU memory bytes transferred between L3 caches and GTI. |
| GtiHdcLookupsThroughput          | The total number of GPU memory bytes transferred between GTI and HDC, when HDC is doing TLB lookups. |
| GtiReadThroughput                | The total number of GPU memory bytes read from GTI. |
| GtiWriteThroughput               | The total number of GPU memory bytes written to GTI. |
| SamplerBottleneck                | The percentage of time in which samplers have been slowing down the pipe when processing EU requests. |
| QueryBeginTime                   | The measurement begin time. |
| CoreFrequencyMHz                 | The last GPU core (unslice) frequency in the measurement. |
| EuSliceFrequencyMHz              | The last GPU Execution Unit slice frequency in the measurement. |
| ReportReason                     | The reason of the report. |
| ContextId                        | The context tag in which report has been taken. |
| CoreFrequencyChanged             | The flag indicating that GPU core frequency has changed. |
| QuerySplitOccurred               | The flag indicating that query has been split during execution on the GPU. |
| ReportId                         | Query report identification number. |
| ReportsCount                     | The number of available query reports. |
| OverrunOccured                   | The flag indicating that Oa buffer has been overran. |
| SampleSequence                   | Number identifying report sequence. |
| SamplePhase                      | Buffer execution phase. |
| GpuNode                          | GPU node buffer was sent to. |

