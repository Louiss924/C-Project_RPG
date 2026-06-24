## ADDED Requirements

### Requirement: Refactor Player and Monster with Base Class
The system SHALL organize Player and Monster entities under a common Character base class to share core attributes and methods.

#### Scenario: Verify Common Base Class
- **WHEN** the code compiles
- **THEN** both Player and Monster classes inherit from Character and share the takeDamage implementation
