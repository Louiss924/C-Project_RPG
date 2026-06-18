## ADDED Requirements

### Requirement: Add New Cards to Player Deck and Draft Pool
The game flow system MUST add the three new offensive cards (Pierce Strike, Armor Smasher, Combo Strike) to the player's 1-1 starting deck and the pre-boss card draft pool.

#### Scenario: Verify New Cards in starting deck
- **WHEN** the player enters battle Level 1-1
- **THEN** the player's starting hand MUST contain Pierce Strike, Armor Smasher, and Combo Strike cards

#### Scenario: Verify New Cards in draft pool
- **WHEN** the card drafting phase starts before entering Round 3
- **THEN** the selection pool MUST include Pierce Strike, Armor Smasher, and Combo Strike cards
