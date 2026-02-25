# Digital Brain Simulation

This project provides a C++20 digital-brain runtime with an interactive communication interface that can be taught safely during a local session.

## Implemented capabilities

- Core neural simulation modules (`Neuron`, `Synapse`, `BrainRegion`, `Connectome`, `SimulationEngine`)
- Pluggable plasticity (`LearningRule`, `HebbianRule`)
- Cognitive bridge (`Agent`) from user text to sensory vectors and action states
- Communication module (`DialogBrain`) with:
  - explicit supervised learning (`teach: input => response`)
  - bounded memory/token growth limits to prevent unbounded resource use
  - deterministic fallback responses without echoing user content
  - no auto-learning from unknown prompts (prevents memory pollution)
- Audit trail module (`AuditTrail`) for state-changing teach actions
- CLI interface with terminal-safe output sanitization

## Build

```bash
cmake -S . -B build -DDBS_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Run

```bash
./build/digital_brain
```

Commands:

- `/help` usage help
- `/memory` show number of stored dialogue patterns
- `/quit` exit

Training format:

- `teach: hello there => Hello, I hear you.`

Audit output:

- Teach actions are recorded to `audit.log.jsonl` at shutdown.

## Safety and fairness notes

- No global mutable brain state is used.
- Profile demographics are metadata only and do not change cognitive ability logic.
- Runtime input storage is bounded.
- No runtime internet dependency.
