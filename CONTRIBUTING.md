# Contributing to Object Placement Manager (OPM)

Thank you for your interest in contributing to OPM! This document provides guidelines and instructions for contributing.

## 🤝 How to Contribute

### Reporting Bugs

If you find a bug, please create an issue with:
- A clear, descriptive title
- Steps to reproduce the bug
- Expected behavior vs actual behavior
- Your Unreal Engine version
- Your operating system
- Screenshots or videos if applicable

### Requesting Features

We love feature requests! Please create an issue with:
- A clear description of the feature
- Use cases and benefits
- Any relevant mockups or examples
- Why this would be useful to the community

### Submitting Code

1. **Fork the Repository**
   - Click the "Fork" button on GitHub
   - Clone your fork locally

2. **Create a Feature Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make Your Changes**
   - Follow the existing code style
   - Add comments for complex logic
   - Update documentation as needed
   - Test your changes thoroughly

4. **Commit Your Changes**
   ```bash
   git add .
   git commit -m "Add: Brief description of your changes"
   ```
   
   Use commit prefixes:
   - `Add:` for new features
   - `Fix:` for bug fixes
   - `Update:` for improvements
   - `Docs:` for documentation
   - `Refactor:` for code refactoring

5. **Push to Your Fork**
   ```bash
   git push origin feature/your-feature-name
   ```

6. **Create a Pull Request**
   - Go to the original repository
   - Click "New Pull Request"
   - Select your branch
   - Fill in the PR template
   - Submit for review

## 📝 Code Style Guidelines

### C++ Code
- Follow Epic's coding standards
- Use descriptive variable names
- Add comments for public APIs
- Keep functions focused and small
- Use `const` where appropriate

### Blueprint/UMG
- Use clear, descriptive names
- Comment complex logic
- Keep graphs organized
- Follow UE naming conventions

### Documentation
- Use clear, simple language
- Include examples where helpful
- Keep formatting consistent
- Update relevant docs with changes

## 🧪 Testing

Before submitting:
- Test your changes in UE5
- Verify no regressions in existing features
- Test on your target platforms
- Include test cases if applicable

## 📚 Documentation

Update documentation when:
- Adding new features
- Changing existing behavior
- Fixing bugs that affect usage
- Improving workflows

Documentation to update:
- README.md (if applicable)
- Plugin README.md
- Code comments
- Wiki pages (when available)

## 🔍 Code Review Process

1. **Submission**
   - PR is submitted
   - Automated checks run (if configured)

2. **Review**
   - Maintainers review code
   - Feedback is provided
   - Discussion if needed

3. **Revision**
   - Address review comments
   - Push updates to your branch
   - Re-request review

4. **Approval**
   - PR is approved
   - Merged into main branch
   - Contributor is credited

## 🌟 Recognition

Contributors will be:
- Listed in CONTRIBUTORS.md
- Credited in release notes
- Acknowledged in the community

## 💡 Development Setup

### Prerequisites
- Unreal Engine 5.3+
- Visual Studio 2022 (Windows) or Xcode (Mac)
- Git

### Setup Steps
1. Fork and clone the repository
2. Open the plugin in Unreal Engine
3. Generate project files
4. Build the plugin
5. Test in the editor

### Building
```bash
# Windows
RunUAT.bat BuildPlugin -Plugin="Path/to/OPM.uplugin" -Package="Output/Path"

# Mac/Linux
RunUAT.sh BuildPlugin -Plugin="Path/to/OPM.uplugin" -Package="Output/Path"
```

## 🎯 Priority Areas

We're especially interested in contributions for:
- Performance optimizations
- Additional placement patterns
- UI/UX improvements
- Documentation and tutorials
- Bug fixes
- Test coverage

## ❓ Questions?

If you have questions:
- Check existing issues and discussions
- Create a new discussion on GitHub
- Review the documentation
- Reach out via issues

## 📋 Pull Request Checklist

Before submitting, ensure:
- [ ] Code follows style guidelines
- [ ] Changes are tested in UE5
- [ ] Documentation is updated
- [ ] Commit messages are clear
- [ ] Branch is up to date with main
- [ ] No merge conflicts
- [ ] PR description is complete

## 🚀 Thank You!

Every contribution, big or small, helps make OPM better for everyone. We appreciate your time and effort!

---

**Happy Contributing! 🎮**
