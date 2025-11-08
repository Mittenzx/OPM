# Changelog

All notable changes to Object Placement Manager will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Phase: Core Implementation (In Progress)

#### Added
- Complete C++ utility class implementations
- PlacementUtilities for pattern generation (grid, circular, line, random)
- AlignmentUtilities for actor alignment and distribution
- NamingUtilities for batch renaming operations
- ActorReplacementUtilities for actor replacement with property preservation
- OrganizationUtilities for level organization (folders, tags, hierarchy)
- OPMBlueprintLibrary for full Blueprint API exposure
- Transaction support (OPMTransactionUtils) for undo/redo
- Comprehensive usage examples (USAGE_EXAMPLES.md)
- Developer contribution guide (DEVELOPER.md)

#### Changed
- Updated README.md with implementation status
- Updated ROADMAP.md to reflect completed features
- Updated IMPLEMENTATION.md with phase completion status

---

## [1.0.0] - TBD (Target: Q1 2026)

### Planned - MVP Release

#### Will Include
- Full C++ utility implementations ✅
- Blueprint API library ✅
- Transaction/undo support ✅
- Editor Utility Widget UI (In Progress)
- Batch object placement tools
- Smart alignment & distribution
- Batch naming utilities
- Quick actor replacement
- Level organization tools
- Documentation and examples
- Demo content
- Video tutorials

#### Target Features for 1.0
- Grid placement (customizable rows, columns, spacing)
- Circular placement (radius, count, start angle)
- Line placement (start/end points, count)
- Random scatter (bounds, count, seed)
- Align actors (left, right, top, bottom, center, front, back)
- Distribute actors (horizontal, vertical, radial)
- Snap to grid
- Batch rename with prefix/suffix/numbering
- Find and replace in names
- Replace actors while preserving transforms
- Set actor folders
- Apply tags
- Create hierarchies

---

## Version History

### Phase 0: Foundation (Completed Nov 2025)
- Initial plugin structure
- Module setup
- Build configuration
- Comprehensive documentation (80,000+ words)
  - README.md
  - ROADMAP.md
  - MARKETPLACE.md
  - IMPLEMENTATION.md
  - FAQ.md
  - QUICKSTART.md
  - INDEX.md
  - PROJECT_STRUCTURE.md
  - CONTRIBUTING.md
  - SUMMARY.md

### Phase 1: Core Implementation (Completed Nov 2025)
- All C++ utility classes
- Blueprint API library
- Transaction support
- Usage examples
- Developer guide

### Phase 2: UI Development (Next)
- Editor Utility Widgets
- Visual interface
- User interaction
- Testing and polish

---

## Notes

### Breaking Changes
- None yet (pre-release)

### Deprecations
- None yet (pre-release)

### Known Issues
- None yet (core implementation phase)

### Migration Guide
- N/A (initial release)

---

## Feedback & Contributions

We welcome feedback and contributions! Please see:
- [CONTRIBUTING.md](CONTRIBUTING.md) for contribution guidelines
- [DEVELOPER.md](DEVELOPER.md) for technical documentation
- [GitHub Issues](https://github.com/Mittenzx/OPM/issues) for bug reports and feature requests

---

**Project Status:** 🟡 In Development (Core Complete, UI In Progress)
**Current Version:** 0.5.0 (Pre-release, Core Implementation)
**Next Release:** 1.0.0 (Full MVP with UI)
