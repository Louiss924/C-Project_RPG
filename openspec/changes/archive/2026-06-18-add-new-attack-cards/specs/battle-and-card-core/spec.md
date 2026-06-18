## ADDED Requirements

### Requirement: New Offensive Card Effects Support
The battle card system MUST support new offensive card effects including true damage, armor break damage, and multi-strike damage.

#### Scenario: Pierce Strike Card Usage
- **WHEN** the player plays the "Pierce Strike" card
- **THEN** the system MUST execute damage calculation and monster.takeDamage bypassing the monster's armor (isTrueDamage = true)

#### Scenario: Armor Smasher Card Usage
- **WHEN** the player plays the "Armor Smasher" card
- **THEN** the system MUST reset the monster's armor to 0 first, and then execute damage calculation to the monster

#### Scenario: Combo Strike Card Usage
- **WHEN** the player plays the "Combo Strike" card
- **THEN** the system MUST execute damage calculation and monster.takeDamage 3 times sequentially
