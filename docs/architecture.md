# Architecture Overview

## Layered flow

```text
User Input -> text->sensory transform -> Agent/SimulationEngine -> cognitive action
      \-> DialogBrain(recall or safe fallback) -> sanitized terminal output
      \-> AuditTrail (teach events) -> audit.log.jsonl
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
  - Stores dialogue examples (`user -> assistant`) with bounded capacity
  - Finds closest prior user message via token-set overlap
  - Only learns new mappings through explicit `Teach(...)`
  - Returns deterministic fallback responses for unknown input
- `AuditTrail`
  - Records teach events with UTC timestamp, user id, action, and outcome

### App layer

- CLI loop in `src/app/main.cpp`
  - Robust command handling (`/help`, `/memory`, `/quit`)
  - Bridges user text into sensory vectors and simulation stepping via `Agent`
  - Sanitizes terminal output to mitigate control-sequence injection
  - Catches exceptions and emits generic user-safe error messages

## Security/compliance-focused design choices

- Input length limits and bounded memory/token maps mitigate memory-exhaustion risk.
- Unknown prompts do not auto-persist, reducing memory pollution.
- User text is not echoed in fallback responses.
- Teach actions produce auditable records.
