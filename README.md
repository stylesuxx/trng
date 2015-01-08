# True Random Number Generator
Arduino based true random number generator. Intended to be used with a geiger counter or a similar device producing impulses based on some entrophy source.

## Concept
The source of enthropy, in my case the pulse pin of a Mightyohm geiger counter, is attached to the Arduinos first interrupt. The deltas of three pulses are measured and compared with each other. Depending on which delta is bigger a bit of a char byte is set. If 8 Bits are collected, the char is printed to the Arduinos serial port.

### Example
    |
    |     |      |           |      |
    |     |--d1--|----d2-----|--d3--|
    |_____|______|___________|______|______
                    time

We start with a zeroed char byte **B00000000** and a *bit counter* on *0*. Then wait for three pulses to get two initial deltas.

In this example *d1* and *d2*, now if the first delta is bigger than the second the bit in the char byte is set according to the bit counter. This is not the case, so we just increase the *bit counter* to *1*. Also *d2* is now our fist delta and we only need to wait for another pulse to get *d3*.

After we got another pulse, the first delta (d2) is bigger than the second on (d3) which means we set the bit on the current *bit counter* position, in this case *1*. After those four pulses we are left with the following char byte: **B00000010**. Again, the *bit counter* is increased. After the bit counter reaches eight, the random char is written to the Arduinos serial port. Also the bit counter and the char byte are reset.