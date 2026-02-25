# Digital Brain Simulation

This project now includes a runnable **interactive communication interface** so you can talk to the simulation, train responses, and see learning behavior improve over time.

## Implemented capabilities

- Core neural simulation modules (`Neuron`, `Synapse`, `BrainRegion`, `Connectome`, `SimulationEngine`)
- Pluggable plasticity (`LearningRule`, `HebbianRule`)
- Cognitive scaffolding (`Agent`, `Planner`)
- Communication module (`DialogBrain`) with:
  - Similarity-based recall of learned responses
  - Direct teaching command (`teach: user input => desired response`)
  - Growing dialogue memory over session time
- CLI interface for two-way communication without template-only output

## Build

```bash
cmake -S . -B build -DDBS_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Run and communicate

```bash
./build/digital_brain
```

Commands:

- `/help` usage help
- `/memory` show number of stored dialogue patterns
- `/quit` exit

Training:

- `teach: hello there => Hello, I hear you.`

After teaching, sending `hello there` returns the taught response.

## Safety and fairness notes

- No global mutable brain state is used.
- Profile demographics are metadata only and do not change cognitive ability logic.
- No runtime internet dependency.
