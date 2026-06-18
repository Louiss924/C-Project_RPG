## ADDED Requirements

### Requirement: Story Dialogue Before and After Combat
The system MUST display story dialogue text before the start of a combat and after a combat victory for Level 1-2 and Level 1-3, and wait for player input before proceeding.

#### Scenario: Show Dialogue Before Battle
- **WHEN** entering the battle of Level 1-2 or Level 1-3 before combat starts
- **THEN** the system MUST display the dialogue screen with text and wait for a keypress to start the battle

#### Scenario: Show Dialogue After Battle Victory
- **WHEN** the player defeats the monster of Level 1-2 or Level 1-3
- **THEN** the system MUST display the victory story dialogue and wait for a keypress before progressing
