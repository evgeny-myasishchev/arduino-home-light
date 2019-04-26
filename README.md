# Home light controller

## Unit tests

Make sure to have reflex installed

```
# Run once
make build-test && ./build/apps/program

# Run all tests on every change
reflex $(cat .reflex) -- sh -c "make build-test && ./build/apps/program"

# Filter logger specific tests
reflex $(cat .reflex) -- sh -c "make build-test && ./build/apps/program --gtest_filter=logger*"
```