/*
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
*/

#include <metrics_discovery/metrics_discovery_helper.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
    // Initialize the MDH context

    MDH_Context mdhContext;
    auto result = mdhContext.Initialize();
    if (result != MDH_Context::RESULT_OK) {
        fprintf(stderr, "error: failed to initialize MDH_Context\n");
        return 1;
    }

    // Iterate over global symbols

    auto device = mdhContext.MDDevice;
    auto deviceParams = device->GetParams();
    auto globalSymbolsCount = deviceParams->GlobalSymbolsCount;
    if (globalSymbolsCount > 0) {
        printf("Global symbols:\n");
        for (uint32_t i = 0; i < globalSymbolsCount; ++i) {
            auto globalSymbol = device->GetGlobalSymbol(i);
            printf("    %s\n", globalSymbol->SymbolName);
        }
    }

    // Iterate over overrides

    uint32_t overrideCount = 0;
    auto driverVersion = MDH_GetDriverVersion(device);
    if ((driverVersion.MajorVersion > 1) ||
        (driverVersion.MajorVersion == 1 && driverVersion.MinorVersion > 1)) {
        overrideCount = ((MetricsDiscovery::SMetricsDeviceParams_1_2*) deviceParams)->OverrideCount;
    }

    if (overrideCount == 0) {
        printf("No overrides available.\n");
    } else {
        printf("Overrides:\n");
        for (uint32_t i = 0; i < overrideCount; ++i) {
            auto ovrride = ((MetricsDiscovery::IMetricsDevice_1_2*) device)->GetOverride(i);
            auto ovrrideParams = ovrride->GetParams();
            printf("    %-40s %s\n", ovrrideParams->SymbolName, ovrrideParams->Description);
        }
    }

    // Iterate over metrics

    printf("Metrics:\n");
    auto concurrentGroupCount = deviceParams->ConcurrentGroupsCount;
    for (uint32_t i = 0; i < concurrentGroupCount; ++i) {
        auto concurrentGroup = device->GetConcurrentGroup(i);
        auto concurrentGroupParams = concurrentGroup->GetParams();

        printf("    %-40s %s\n", concurrentGroupParams->SymbolName, concurrentGroupParams->Description);

        auto metricSetsCount = concurrentGroupParams->MetricSetsCount;
        for (uint32_t j = 0; j < metricSetsCount; ++j) {
            auto metricSet = concurrentGroup->GetMetricSet(j);
            auto metricSetParams = metricSet->GetParams();

            printf("        %-36s %s\n", metricSetParams->SymbolName, metricSetParams->ShortName);

            auto metricsCount = metricSetParams->MetricsCount;
            for (uint32_t k = 0; k < metricsCount; ++k) {
                auto metric = metricSet->GetMetric(k);
                auto metricParams = metric->GetParams();

                printf("            %-32s %s\n", metricParams->SymbolName, metricParams->LongName);
            }

            auto infoCount = metricSetParams->InformationCount;
            for (uint32_t k = 0; k < infoCount; ++k) {
                auto info = metricSet->GetInformation(k);
                auto infoParams = info->GetParams();

                printf("            %-32s %s\n", infoParams->SymbolName, infoParams->LongName);
            }
        }
    }

    // Clean up the metric memory and context

    mdhContext.Finalize();

    return 0;
}
