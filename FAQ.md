# Frequently Asked Questions - Object Placement Manager

## General Questions

### What is Object Placement Manager (OPM)?
OPM is an Unreal Engine editor plugin that automates common level design tasks like batch object placement, alignment, naming, and organization. It saves developers hours of repetitive manual work.

### Who is OPM for?
- Solo indie developers
- Small game development teams (2-5 people)
- Level designers and technical artists
- Architectural visualization professionals
- Anyone who works with Unreal Engine and wants to save time

### Why should I use OPM instead of doing things manually?
**Time savings:** What takes 30 minutes manually takes 30 seconds with OPM.

Example scenarios:
- Placing 100 objects in a grid: Manual = 20+ minutes, OPM = 10 seconds
- Aligning 50 props: Manual = 10+ minutes, OPM = 5 seconds
- Renaming 200 actors: Manual = 15+ minutes, OPM = 30 seconds

**Consistency:** Perfect alignment and spacing every time, no human error.

**Professional results:** Clean, organized projects with consistent naming conventions.

---

## Purchase & Licensing

### How much does OPM cost?
- **Launch Price:** $24.99
- **Introductory Discount:** 20% off (first 2 weeks)
- **Updates:** Free lifetime updates included

### Where can I buy OPM?
- **Primary:** Fab Marketplace (Epic Games)
- **Alternative:** Direct from GitHub (development version)

### What's included in my purchase?
- Full plugin with all features
- Complete C++ source code
- Comprehensive documentation (35,000+ words)
- Video tutorial series
- Example project/demo
- Lifetime updates
- Community support

### Can I use OPM in commercial projects?
**Yes!** No additional licensing required. Use OPM in:
- Commercial games
- Architectural visualization projects
- Training simulations
- Any Unreal Engine project

### Do I need a separate license for each team member?
**No.** One purchase covers your entire team/studio for that project. However, we appreciate if larger studios purchase additional licenses to support development.

### Is there a free trial?
Check the Fab marketplace for:
- Demo version (limited features)
- Seasonal promotions
- Educational discounts (if applicable)

### What's your refund policy?
Follow Epic's standard Fab marketplace refund policy. We also offer:
- 30-day satisfaction guarantee
- Responsive support to resolve issues
- We want you to be happy with your purchase!

---

## Technical Questions

### What Unreal Engine versions are supported?
- **Current:** Unreal Engine 5.3+
- **Planned:** UE 5.4, 5.5 (automatic with updates)
- **Possible:** UE4.27 (if community requests it)

### What platforms does OPM support?
- **Windows:** Win64 (fully supported)
- **Mac:** macOS 11+ (fully supported)
- **Linux:** Ubuntu 20.04+ (fully supported)

### Does OPM affect runtime performance?
**No.** OPM is an editor-only plugin. It has:
- Zero runtime overhead
- No impact on packaged games
- No shipping code included
- Only used during development

### Can I use OPM with Blueprint?
**Yes!** All OPM features are exposed to Blueprint via a Blueprint Function Library. You can:
- Call OPM functions from Blueprint
- Create custom editor utilities
- Automate your own workflows
- Extend OPM's functionality

### Can I use OPM with Python?
**Planned for v1.5.** Python scripting support is on the roadmap based on community interest.

### Is the source code included?
**Yes!** Full C++ source code is included, allowing you to:
- Customize functionality
- Extend with new features
- Learn from the implementation
- Fix bugs yourself (or contribute back!)

### What are the system requirements?
If you can run Unreal Engine, you can run OPM:
- Same requirements as your UE version
- Minimal additional disk space (~10MB)
- No special hardware needed
- No external dependencies

---

## Installation & Setup

### How do I install OPM?
**From Fab Marketplace:**
1. Purchase OPM
2. Open Epic Games Launcher
3. Go to Library → Plugins
4. Install OPM to Engine or Project
5. Restart Unreal Engine
6. Enable in Edit → Plugins

**From GitHub:**
1. Clone or download repository
2. Copy `Plugins/OPM` to your project's `Plugins` folder
3. Restart Unreal Engine
4. Enable in Edit → Plugins

### Do I need to rebuild my project?
Usually not. But if prompted:
- Click "Yes" to rebuild
- Wait for compilation
- Restart editor

### Where do I find OPM after installation?
- **Toolbar:** New OPM button in editor toolbar
- **Menu:** Window → Object Placement Manager
- **Content Browser:** Plugins → OPM Content

### Can I install OPM to the engine instead of my project?
**Yes!** Installing to the engine makes OPM available to all your projects.

### How do I update OPM?
- **Fab Marketplace:** Updates appear in your library automatically
- **GitHub:** Pull latest changes from repository

### I get a compilation error. What should I do?
1. Check your UE version (must be 5.3+)
2. Verify Visual Studio is installed correctly
3. Try regenerating project files
4. Check GitHub Issues for known problems
5. Contact support with error details

---

## Features & Usage

### What can OPM do?
**Main Features:**
1. **Batch Placement** - Place objects in patterns (grid, circle, line, random)
2. **Alignment** - Align and distribute actors perfectly
3. **Naming** - Batch rename with prefixes, suffixes, numbering
4. **Replacement** - Replace actors while preserving transforms
5. **Organization** - Group and organize level hierarchies

### How do I place objects in a grid?
1. Select asset in Content Browser
2. Open OPM → Placement tab
3. Choose "Grid" pattern
4. Set rows, columns, spacing
5. Click "Place Objects"

### Can I preview placements before applying?
**Yes!** Enable "Show Preview" to see:
- Temporary visualization of pattern
- Adjust parameters in real-time
- Apply when satisfied
- Cancel if not right

### Does OPM support undo?
**Yes!** All operations support Ctrl+Z undo:
- Place 100 objects → Undo removes all 100
- Rename batch → Undo restores names
- Full transaction system support

### Can I create custom placement patterns?
**Coming in v1.1!** Pattern preset system will let you:
- Save custom configurations
- Share with team
- Build pattern library

**Coming in v1.5!** Custom pattern editor for:
- Fully custom algorithms
- Mathematical patterns
- Procedural arrangements

### How many objects can OPM place at once?
**Tested up to 10,000 objects.** Performance depends on:
- Object complexity (Blueprint vs Static Mesh)
- Your hardware
- Pattern type
- Preview enabled/disabled

**Recommendation:** Start with smaller batches (100-500) and scale up.

### Can OPM place Blueprint actors?
**Yes!** OPM works with:
- Static Meshes
- Blueprint actors
- Particle systems
- Lights
- Volumes
- Any actor type

### Does OPM work with landscape/terrain?
**Basic support now**, **advanced in v2.0:**
- Current: Manual placement on terrain
- Future: Automatic surface projection
- Future: Terrain-aware distribution
- Future: Biome-based placement

---

## Workflow Questions

### How do I use OPM for architectural visualization?
**Common workflows:**

**Windows in a building:**
```
1. Grid pattern
2. Rows = floors, Columns = windows per floor
3. Spacing = window dimensions
4. Adjust individual windows as needed
```

**Tile floors:**
```
1. Grid pattern with precise spacing
2. Tile size spacing
3. Material variants for randomness
```

**Furniture arrangement:**
```
1. Place items individually
2. Use Alignment tools to organize
3. Distribute evenly
4. Name by room/type
```

### How do I organize a large level with OPM?
**Best practices:**

1. **Name everything** (Naming utilities)
   - Consistent prefixes: Props_, Light_, Trigger_
   - Numbers: 001, 002, 003
   - Descriptive: Props_Table_001

2. **Create hierarchy** (Organization tools)
   - Group by type
   - Group by location
   - Parent to organizational actors

3. **Use folders**
   - World Outliner folders
   - Group related objects
   - Scene sections

4. **Tag actors**
   - Functional tags
   - Search and filter
   - Batch operations

### Can I use OPM for game level design?
**Absolutely!** Common uses:

**Collectibles:**
- Scatter in patterns
- Name sequentially
- Easy to track

**Enemy spawns:**
- Random distribution
- Circular patrol paths
- Organized naming

**Modular buildings:**
- Grid placement for pieces
- Perfect alignment
- Quick assembly

**Props and details:**
- Batch placement
- Quick replacement
- Efficient iteration

### How do I work faster with OPM?
**Pro tips:**

1. **Learn keyboard shortcuts**
   - Set up custom shortcuts
   - Quick access to common tools

2. **Use preview liberally**
   - Check before placing
   - Avoid mistakes

3. **Save common configurations**
   - Document your patterns
   - Reuse successful setups

4. **Combine operations**
   - Place → Align → Name → Group
   - Efficient workflows

5. **Work in batches**
   - Group similar tasks
   - Process together

---

## Troubleshooting

### OPM isn't showing up after installation
**Checklist:**
- [ ] Plugin enabled in Edit → Plugins?
- [ ] Editor restarted after enabling?
- [ ] Correct UE version (5.3+)?
- [ ] Plugin in correct folder?

### "Can't place objects" error
**Common causes:**
- No actor class selected
- Viewport not in focus
- Level locked or read-only
- Insufficient permissions

**Solutions:**
- Select asset first
- Click in viewport
- Check level properties
- Verify write access

### Alignment tools aren't working
**Check:**
- At least 2 actors selected?
- Actors are movable (not static)?
- Correct alignment type selected?

### Performance is slow with many objects
**Optimization:**
- Disable preview for large batches
- Use simpler actor types
- Place in smaller groups
- Consider hardware limits

### Preview isn't showing
**Troubleshooting:**
- "Show Preview" checked?
- Preview color visible against background?
- Viewport rendering correctly?
- Try refreshing viewport (F5)

### Undo isn't working
**Note:** Some operations may have limitations.
- Most operations fully support undo
- Report persistent issues to GitHub

---

## Support & Community

### How do I get help?
1. **Check documentation**
   - README files
   - This FAQ
   - Quick Start Guide
   - Implementation docs

2. **Search GitHub Issues**
   - Existing solutions
   - Known problems
   - Workarounds

3. **Ask the community**
   - GitHub Discussions
   - Epic Developer Forums
   - Unreal Engine communities

4. **Contact support**
   - GitHub Issues (bug reports)
   - GitHub Discussions (questions)
   - Email (via GitHub profile)

### How do I report a bug?
**Create a GitHub Issue with:**
- Clear title describing the bug
- Steps to reproduce
- Expected vs actual behavior
- UE version and OS
- Screenshots/video if helpful
- Log files if crashes

### How do I request a feature?
**Open a GitHub Discussion or Issue:**
- Describe the feature clearly
- Explain use cases
- Why it would be valuable
- Examples or mockups if possible

### Can I contribute to OPM?
**Yes! We welcome contributions:**
- Bug fixes
- New features
- Documentation improvements
- Tutorial creation
- Testing and feedback

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Is there a Discord server?
**Not yet.** We're starting with:
- GitHub Discussions
- GitHub Issues
- Epic Developer Forums

If demand grows, we'll create a Discord community.

### How often is OPM updated?
**Regular schedule:**
- **Bug fixes:** As needed (hotfixes)
- **Minor updates:** Every 2-3 months
- **Major updates:** Every 6-12 months
- **Communication:** GitHub releases, patch notes

---

## Business & Development

### Who develops OPM?
Created by **Mittenzx**, an indie developer focused on creating quality tools for the Unreal Engine community.

### Is OPM open source?
**Hybrid approach:**
- Source code included with purchase
- MIT License for modification
- Commercial use allowed
- Contributions welcome

### Will OPM always be developed?
**Commitment:**
- Active development planned for years
- Regular updates and support
- Community-driven features
- Long-term roadmap

**Sustainability:**
- Revenue supports development
- Growing user base enables more features
- Community contributions help

### Can I become an OPM partner/affiliate?
**Interested in:**
- Tutorial creators
- Tool reviewers
- Community leaders
- Training providers

Contact via GitHub to discuss partnership opportunities.

### Can I white-label or resell OPM?
**No.** OPM is sold exclusively through:
- Fab Marketplace (official)
- GitHub (development version)

You can:
- Build tools that extend OPM
- Create training content
- Offer consulting services

### Will there be OPM Pro?
**Possibly in v3.0+** depending on:
- Community feedback
- Studio needs
- Feature complexity

Potential Pro features:
- Multi-user collaboration
- Enterprise support
- Advanced APIs
- Custom development

---

## Comparison Questions

### How is OPM different from Editor Utility Widgets?
OPM **IS** built with Editor Utility Widgets, but:
- Pre-built, professional tools
- No setup required
- Comprehensive features
- Well documented
- Actively maintained
- Community support

vs. EUW from scratch:
- Requires development time
- Need technical skills
- Maintenance burden
- No community

### How does OPM compare to other marketplace tools?
**OPM's advantages:**
- **Focused:** Does specific tasks excellently
- **Affordable:** $24.99 vs $50-100+ competitors
- **Documented:** 35,000+ words of documentation
- **Simple:** 5-minute learning curve
- **Supported:** Active development, responsive support

**When to choose others:**
- Need all-in-one mega-suites
- Need very specific niche features
- Have large budget

### Should I build my own tools instead?
**Consider:**
- **Time:** Days/weeks to build, test, maintain
- **Cost:** Your time value vs $24.99
- **Quality:** Professional vs quick hack
- **Support:** Maintenance burden
- **Updates:** UE version compatibility

**OPM makes sense if:**
- Want to focus on your game, not tools
- Value time over complete customization
- Want professional quality
- Need ongoing support

---

## Future Plans

### What features are coming next?
See [ROADMAP.md](ROADMAP.md) for detailed plans.

**v1.1 (3 months):**
- Pattern presets
- More patterns
- Performance improvements

**v1.5 (6 months):**
- Advanced API
- Material tools
- Smart placement

**v2.0 (12 months):**
- AI features
- VR support
- Landscape integration

### Can I vote on features?
**Yes!** Influence development by:
- Commenting on feature issues
- Reacting to proposals
- Participating in polls
- Sharing use cases

### Will OPM expand to other tools?
**Long-term vision** includes complementary tools:
- OPM Lighting Suite
- OPM Material Manager
- OPM Asset Optimizer
- Complete Bundle

Each focused, quality tool for specific workflows.

### Will OPM support Unreal Engine 6?
**Yes!** When UE6 releases:
- Day-one compatibility (or soon after)
- Continued support for UE5
- Migration guides if needed

---

## Still Have Questions?

**Can't find your answer?**
1. Search the full documentation
2. Check GitHub Issues
3. Ask in GitHub Discussions
4. Contact support

**Documentation:**
- [README.md](README.md) - Project overview
- [Plugins/OPM/README.md](Plugins/OPM/README.md) - User guide
- [QUICKSTART.md](QUICKSTART.md) - Quick start guide
- [IMPLEMENTATION.md](IMPLEMENTATION.md) - Technical details
- [ROADMAP.md](ROADMAP.md) - Future plans

**Community:**
- [GitHub Issues](https://github.com/Mittenzx/OPM/issues)
- [GitHub Discussions](https://github.com/Mittenzx/OPM/discussions)

---

**We're here to help make your workflow better! 🚀**

*Last updated: November 2025*
