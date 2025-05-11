#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define SIZE 501
#define PI 3.1415926
#define DIFF 0.01
#define DURATION 1.0 // Signal duration in seconds

using namespace std;

// ======== Abstract Base Class for Waveforms ========
class Wave {
public:
    double frequency, amplitude, phase_offset;

    // Constructor to initialize common properties
    Wave(double freq, double amp, double phase)
        : frequency(freq), amplitude(amp), phase_offset(phase) {}

    // Abstract methods to be implemented by derived classes
    virtual void show() const = 0;
    virtual void generate() = 0;
    virtual void show_samples() const = 0;
};

// ======== Sine Wave Class ========
class SineWave : public Wave {
public:
    double sampling_freq;             // Sampling frequency in Hz
    double time_interval;             // Time between samples
    int sample_index = 0;             // Number of samples generated (<= SIZE)
    vector<double> samples;           // Stores sampled sine values

    // Constructor
    SineWave(double freq, double amp, double phase, double samp_freq)
        : Wave(freq, amp, phase), sampling_freq(samp_freq) {}

    // Generate sine wave samples
    void generate() override {
        double theta = (phase_offset == 90.0) ? PI / 2.0 : 0.0;
        double t = 0.0;
        time_interval = 1.0 / sampling_freq;

        for (int i = 0; i < SIZE; ++i) {
            samples.push_back(amplitude * sin((2 * PI * frequency * t) + theta));
            t += time_interval;
        }
    }

    // Display the generated sine wave samples
    void show_samples() const override {
        cout << "\n--- Sine Wave Output ---\n";
        cout << "Freq: " << frequency << "Hz, Sampling: " << sampling_freq << "Hz, Duration: " << DURATION << "s\n";

        double t = 0.0;
        for (int i = 0; i < SIZE; ++i) {
            if (t > DURATION + DIFF) break; // stop after approx. 1 second
            cout << samples[i] << '\n';
            t += time_interval;
        }
    }

    // Display basic sine wave info
    void show() const override {
        cout << "\n[Sine Wave Info]\n";
        cout << "Freq: " << frequency << "Hz\nAmplitude: " << amplitude
             << "\nPhase Offset: " << phase_offset << "°\nSampling Freq: " << sampling_freq << "Hz\n";
    }
};

// ======== Square Wave Class ========
class SquareWave : public Wave {
public:
    double sampling_freq;             // Sampling frequency in Hz
    double time_interval;             // Time between samples
    int sample_index = 0;             // Number of samples generated (<= SIZE)
    vector<double> samples;           // Stores sampled square values

    // Constructor
    SquareWave(double freq, double amp, double phase, double samp_freq)
        : Wave(freq, amp, phase), sampling_freq(samp_freq) {}

    // Sign function to generate square wave values
    double sign(double val) const {
        if (val > 0) return amplitude;
        if (val < 0) return -amplitude;
        return 0.0;
    }

    // Generate square wave samples by taking sign of sine
    void generate() override {
        double theta = (phase_offset == 90.0) ? PI / 2.0 : 0.0;
        double t = 0.0;
        time_interval = 1.0 / sampling_freq;

        for (int i = 0; i < SIZE; ++i) {
            double result = amplitude * sin((2 * PI * frequency * t) + theta);
            samples.push_back(sign(result));
            t += time_interval;
        }
    }

    // Display the generated square wave samples
    void show_samples() const override {
        cout << "\n--- Square Wave Output ---\n";
        cout << "Freq: " << frequency << "Hz, Sampling: " << sampling_freq << "Hz, Duration: " << DURATION << "s\n";

        double t = 0.0;
        for (int i = 0; i < SIZE; ++i) {
            if (t > DURATION + DIFF) break;
            cout << samples[i] << '\n';
            t += time_interval;
        }
    }

    // Display basic square wave info
    void show() const override {
        cout << "\n[Square Wave Info]\n";
        cout << "Freq: " << frequency << "Hz\nAmplitude: " << amplitude
             << "\nPhase Offset: " << phase_offset << "°\nSampling Freq: " << sampling_freq << "Hz\n";
    }
};

// ======== Main Program Entry Point ========
int main() {
    // Create and generate sine wave
    SineWave sine_wave(10, 3, 90, 200); // 10Hz, amplitude 3, 90° phase, 200Hz sampling
    sine_wave.generate();
    sine_wave.show_samples();

    // Create and generate square wave
    SquareWave square_wave(40, 1, 0, 200); // 40Hz, amplitude 1, 0° phase, 200Hz sampling
    square_wave.generate();
    square_wave.show_samples();

    // Determine max samples for mixed signal
    int max_len = min(sine_wave.samples.size(), square_wave.samples.size());

    // Multiply sine and square to create mixed signal
    vector<double> mixed_signal;
    for (int i = 0; i < max_len; ++i) {
        mixed_signal.push_back(sine_wave.samples[i] * square_wave.samples[i]);
    }

    // Output mixed signal
    cout << "\n--- Mixed Signal Output ---\n";
    for (double val : mixed_signal) {
        cout << val << '\n';
    }

    // Calculate mean of the first quarter (0 to 0.25s)
    int quarter_len = max_len / 4;
    double mean = accumulate(mixed_signal.begin(), mixed_signal.begin() + quarter_len, 0.0) / quarter_len;
    cout << "\nMean of mixed signal (first 0.25s): " << mean << '\n';

    // Calculate "integral" (sum) of the second quarter (0.25s to 0.5s)
    double integral = accumulate(mixed_signal.begin() + quarter_len, mixed_signal.begin() + 2 * quarter_len, 0.0);
    cout << "Integral of second quarter: " << integral << '\n';

    return 0;
}
