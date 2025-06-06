/*
  ==============================================================================

   This file is part of the JUCE framework.
   Copyright (c) Raw Material Software Limited

   JUCE is an open source framework subject to commercial or open source
   licensing.

   By downloading, installing, or using the JUCE framework, or combining the
   JUCE framework with any other source code, object code, content or any other
   copyrightable work, you agree to the terms of the JUCE End User Licence
   Agreement, and all incorporated terms including the JUCE Privacy Policy and
   the JUCE Website Terms of Service, as applicable, which will bind you. If you
   do not agree to the terms of these agreements, we will not license the JUCE
   framework to you, and you must discontinue the installation or download
   process and cease use of the JUCE framework.

   JUCE End User Licence Agreement: https://juce.com/legal/juce-8-licence/
   JUCE Privacy Policy: https://juce.com/juce-privacy-policy
   JUCE Website Terms of Service: https://juce.com/juce-website-terms-of-service/

   Or:

   You may also use this code under the terms of the AGPLv3:
   https://www.gnu.org/licenses/agpl-3.0.en.html

   THE JUCE FRAMEWORK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL
   WARRANTIES, WHETHER EXPRESSED OR IMPLIED, INCLUDING WARRANTY OF
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

namespace juce
{

//==============================================================================
/**
    A random number generator.

    You can create a Random object and use it to generate a sequence of random numbers.

    @tags{Core}
*/
class JUCE_API  Random  final
{
public:
    //==============================================================================
    /** Creates a Random object based on a seed value.

        For a given seed value, the subsequent numbers generated by this object
        will be predictable, so a good idea is to set this value based
        on the time, e.g.

        new Random (Time::currentTimeMillis())
    */
    explicit Random (int64 seedValue) noexcept;

    /** Creates a Random object using a random seed value.
        Internally, this calls setSeedRandomly() to randomise the seed.
    */
    Random();

    /** Returns the next random 32 bit integer.
        @returns a random integer from the full range 0x80000000 to 0x7fffffff
    */
    int nextInt() noexcept;

    /** Returns the next random number, limited to a given range.
        The maxValue parameter may not be negative, or zero.
        @returns a random integer between 0 (inclusive) and maxValue (exclusive).
    */
    int nextInt (int maxValue) noexcept;

    /** Returns the next random number, limited to a given range.
        @returns a random integer between the range start (inclusive) and its end (exclusive).
    */
    int nextInt (Range<int> range) noexcept;

    /** Returns the next 64-bit random number.
        @returns a random integer from the full range 0x8000000000000000 to 0x7fffffffffffffff
    */
    int64 nextInt64() noexcept;

    /** Returns the next random floating-point number.
        @returns a random value in the range 0 (inclusive) to 1.0 (exclusive)
    */
    float nextFloat() noexcept;

    /** Returns the next random floating-point number.
        @returns a random value in the range 0 (inclusive) to 1.0 (exclusive)
    */
    double nextDouble() noexcept;

    /** Returns the next random boolean value. */
    bool nextBool() noexcept;

    /** Returns a BigInteger containing a random number.
        @returns a random value in the range 0 to (maximumValue - 1).
    */
    BigInteger nextLargeNumber (const BigInteger& maximumValue);

    /** Fills a block of memory with random values. */
    void fillBitsRandomly (void* bufferToFill, size_t sizeInBytes);

    /** Sets a range of bits in a BigInteger to random values. */
    void fillBitsRandomly (BigInteger& arrayToChange, int startBit, int numBits);

    //==============================================================================
    /** Resets this Random object to a given seed value. */
    void setSeed (int64 newSeed) noexcept;

    /** Returns the RNG's current seed. */
    int64 getSeed() const noexcept                      { return seed; }

    /** Merges this object's seed with another value.
        This sets the seed to be a value created by combining the current seed and this
        new value.
    */
    void combineSeed (int64 seedValue) noexcept;

    /** Reseeds this generator using a value generated from various semi-random system
        properties like the current time, etc.

        Because this function convolves the time with the last seed value, calling
        it repeatedly will increase the randomness of the final result.
    */
    void setSeedRandomly();

    /** The overhead of creating a new Random object is fairly small, but if you want
        to avoid it, you can call this method to get a global shared Random object.

        Note this will return a different object per thread it's accessed from,
        making it thread safe. However, it's therefore important not store a reference
        to this object that will later be accessed from other threads.
    */
    static Random& getSystemRandom() noexcept;

private:
    //==============================================================================
    int64 seed;

    #if JUCE_ASSERTIONS_ENABLED_OR_LOGGED
     bool isSystemRandom = false;
    #endif

    JUCE_LEAK_DETECTOR (Random)
};

} // namespace juce
