# OPM Forum Engagement Bot

Automated forum engagement and community management tool for the Object Placement Manager project.

## Overview

This bot helps automate and manage community engagement across multiple platforms:
- Epic Developer Community Forums
- Reddit (r/unrealengine, r/gamedev, r/leveldesign)
- Unreal Slackers Discord
- Twitter/X

## Features

- **Template-based Post Generation**: Use pre-defined templates from FORUM_ENGAGEMENT.md
- **Scheduled Posting**: Plan and schedule posts across platforms
- **Engagement Tracking**: Monitor views, replies, and engagement metrics
- **Analytics Dashboard**: Track posting history and effectiveness
- **Content Calendar**: Follow the recommended 4-week engagement plan
- **Smart Recommendations**: Get suggestions for what to post next

## Installation

### Requirements

- Python 3.8 or higher
- pip (Python package manager)

### Setup

1. **Install dependencies:**
   ```bash
   pip install -r requirements.txt
   ```

2. **Create configuration file:**
   ```bash
   cp forum_bot_config.example.json forum_bot_config.json
   ```

3. **Edit configuration:**
   - Add your platform credentials (if using APIs)
   - Customize posting schedule
   - Set engagement rules

4. **Set up platform credentials (optional):**
   
   For API integrations, create a `.env` file:
   ```bash
   # Reddit
   REDDIT_CLIENT_ID=your_client_id
   REDDIT_CLIENT_SECRET=your_client_secret
   REDDIT_USERNAME=your_username
   REDDIT_PASSWORD=your_password
   
   # Discord
   DISCORD_BOT_TOKEN=your_bot_token
   
   # Twitter
   TWITTER_API_KEY=your_api_key
   TWITTER_API_SECRET=your_api_secret
   TWITTER_ACCESS_TOKEN=your_access_token
   TWITTER_ACCESS_SECRET=your_access_secret
   ```

## Usage

### Basic Commands

**Generate a post from template:**
```bash
python forum_engagement_bot.py --action generate --template introduction
```

**Save generated post to file:**
```bash
python forum_engagement_bot.py --action generate --template feature_showcase --output post.txt
```

**Schedule a post:**
```bash
python forum_engagement_bot.py --action schedule --platform epic_forums --template development_update --title "OPM Update: New Features"
```

**Post immediately (dry-run mode):**
```bash
python forum_engagement_bot.py --action post --platform reddit --template feedback_request
```

**Monitor engagement:**
```bash
python forum_engagement_bot.py --action monitor
```

**Generate analytics report:**
```bash
python forum_engagement_bot.py --action analytics --output report.txt
```

**Get posting recommendations:**
```bash
python forum_engagement_bot.py --action recommend
```

### Available Templates

1. **introduction** - Introduce OPM to the community
2. **feature_showcase** - Demonstrate specific features
3. **feedback_request** - Ask for community input
4. **development_update** - Share progress updates
5. **problem_solving** - Show how OPM solves problems

### Example Workflow

**Week 1: Introduction Phase**
```bash
# Day 1: Generate introduction post
python forum_engagement_bot.py --action generate --template introduction --output day1_epic.txt

# Manually review and post to Epic Forums

# Day 3: Cross-post to Reddit
python forum_engagement_bot.py --action generate --template introduction --output day3_reddit.txt

# Day 5: Share on Twitter (shortened version)
python forum_engagement_bot.py --action generate --template introduction --output day5_twitter.txt
```

**Week 2: Feature Demonstrations**
```bash
# Generate feature showcase
python forum_engagement_bot.py --action generate --template feature_showcase --output feature_demo.txt

# Monitor engagement
python forum_engagement_bot.py --action monitor
```

**Ongoing: Analytics and Planning**
```bash
# Weekly analytics check
python forum_engagement_bot.py --action analytics

# Get recommendations for next posts
python forum_engagement_bot.py --action recommend
```

## Configuration

### Configuration File Structure

```json
{
  "project_name": "Object Placement Manager (OPM)",
  "github_url": "https://github.com/Mittenzx/OPM",
  "platforms": {
    "epic_forums": {
      "enabled": true,
      "base_url": "https://dev.epicgames.com/community/"
    },
    "reddit": {
      "enabled": true,
      "subreddits": ["unrealengine", "gamedev", "leveldesign"]
    },
    "discord": {
      "enabled": true,
      "servers": ["Unreal Slackers"]
    },
    "twitter": {
      "enabled": true,
      "hashtags": ["#UnrealEngine", "#UE5", "#GameDev"]
    }
  },
  "posting_schedule": {
    "frequency_days": 3,
    "preferred_times": ["09:00", "14:00", "18:00"]
  },
  "engagement_rules": {
    "max_posts_per_day": 2,
    "min_response_time_hours": 1,
    "max_response_time_hours": 24
  }
}
```

### Customizing Templates

Templates are defined in the bot code but can be customized. Edit `forum_engagement_bot.py` and modify the templates in the `_load_templates()` method.

Variables you can use in templates:
- `{github_url}` - GitHub repository URL
- `{project_name}` - Project name
- `{feature_name}` - Feature being showcased
- `{example_action}` - Example of what the feature does
- `{update_content}` - Update details
- `{problem_description}` - Problem being solved
- And more (see template definitions)

## Platform Integration

### Manual Posting (Current Default)

The bot generates post content that you manually copy and post to platforms. This is the recommended approach for:
- Personal touch and authenticity
- Compliance with platform rules
- Better engagement quality

### API Integration (Optional)

For automated posting, you can extend the bot with platform APIs:

1. **Reddit** - Uses PRAW library
2. **Discord** - Uses discord.py library
3. **Twitter** - Uses tweepy library
4. **Epic Forums** - Manual (no public API)

To enable API posting, uncomment and implement the platform-specific methods in `post_to_platform()`.

## Tracking and Analytics

The bot maintains engagement data in `engagement_data.json`:

```json
{
  "posts": [
    {
      "id": "post_1",
      "platform": "epic_forums",
      "title": "Introducing OPM",
      "posted_at": "2025-11-09T10:00:00",
      "status": "posted",
      "engagement": {
        "views": 150,
        "replies": 12,
        "upvotes": 45
      }
    }
  ],
  "analytics": {
    "total_posts": 1,
    "platforms": {...}
  }
}
```

Update engagement metrics manually or implement API polling.

## Best Practices

### DO:
✅ Review and customize generated posts before publishing
✅ Add personal touches and context
✅ Respond to comments within 24 hours
✅ Track engagement metrics
✅ Follow the content calendar
✅ Be authentic and helpful

### DON'T:
❌ Auto-post without review
❌ Spam multiple platforms with identical content
❌ Ignore community rules
❌ Over-promote (follow the 80/20 rule: 80% value, 20% promotion)
❌ Post more than 2 times per day

## Troubleshooting

**Bot won't start:**
- Check Python version: `python --version` (need 3.8+)
- Install dependencies: `pip install -r requirements.txt`
- Check config file exists and is valid JSON

**Template errors:**
- Ensure all required variables are provided
- Check template syntax in bot code
- Review error messages in `forum_bot.log`

**API integration issues:**
- Verify credentials in `.env` file
- Check platform API status
- Review API rate limits
- Check `forum_bot.log` for detailed errors

## Files

- `forum_engagement_bot.py` - Main bot script
- `requirements.txt` - Python dependencies
- `forum_bot_config.json` - Configuration file (create from example)
- `engagement_data.json` - Tracking data (auto-generated)
- `forum_bot.log` - Activity log (auto-generated)
- `.env` - Platform credentials (create manually, not in git)

## Support

For issues or questions:
1. Check this README
2. Review [FORUM_ENGAGEMENT.md](../FORUM_ENGAGEMENT.md)
3. Check bot logs: `forum_bot.log`
4. Open an issue on GitHub

## Contributing

To improve the bot:
1. Fork the repository
2. Make your changes
3. Test thoroughly
4. Submit a pull request

## License

MIT License - Same as the OPM project

## Version History

**v1.0 (November 2025)**
- Initial release
- Template-based post generation
- Engagement tracking
- Analytics reporting
- Content calendar support

**Planned Features:**
- Automated API posting
- Real-time engagement monitoring
- Advanced analytics with charts
- Multi-account support
- Webhook notifications
- AI-powered content suggestions

---

**Ready to engage with the community? Start with:**
```bash
python forum_engagement_bot.py --action recommend
```

For full community engagement strategy, see [FORUM_ENGAGEMENT.md](../FORUM_ENGAGEMENT.md)
