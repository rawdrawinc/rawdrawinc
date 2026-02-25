# Architecture Overview

## Layered flow

```text
User Input -> DialogBrain -> (memory match or composed reply) -> Response Output
                     \-> SimulationEngine Tick (background neural update)
```

## Modules

### Core simulation (`brain::core`)

- `Neuron`: leaky integrate-and-fire unit
- `Synapse`: weighted directed edge
- `BrainRegion`: neuron population and local plasticity
- `Connectome`: named region graph container
- `SimulationEngine`: deterministic timestep progression
- `LearningRule`/`HebbianRule`: strategy-based plasticity updates

### Communication (`brain::communication`)

- `DialogBrain`
  - Stores dialogue examples (`user -> assistant`)
  - Finds closest prior user message via token-set overlap
  - Returns learned answer when confidence threshold is met
  - Supports explicit supervised learning through `Teach(...)`

### App layer

- CLI loop in `src/app/main.cpp`
  - Robust command handling (`/help`, `/memory`, `/quit`)
  - No busy-wait loops
  - Input validation for teaching format

## Why this addresses communication requirement

- You can directly converse with the program.
- The program updates behavior using new dialogue examples.
- Repeated communication increases retrievable memory patterns.
- Direct corrections can be injected immediately and reused.
