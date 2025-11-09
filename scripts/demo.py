#!/usr/bin/env python3
"""
Quick demo of the Forum Engagement Bot capabilities
"""

from forum_engagement_bot import ForumEngagementBot

def main():
    print("=" * 70)
    print("OPM FORUM ENGAGEMENT BOT - DEMO")
    print("=" * 70)
    print()
    
    # Initialize bot
    bot = ForumEngagementBot('forum_bot_config.json')
    
    # Demo 1: Generate introduction post
    print("📝 DEMO 1: Generate Introduction Post")
    print("-" * 70)
    post = bot.generate_post('introduction')
    print(post[:200] + "...")
    print()
    
    # Demo 2: Generate feature showcase with variables
    print("📝 DEMO 2: Generate Feature Showcase")
    print("-" * 70)
    post = bot.generate_post(
        'feature_showcase',
        feature_name="batch placement patterns",
        example_action="placed 50 columns in a circular pattern in under 10 seconds",
        feature_list="- Grid patterns\n- Circular patterns\n- Linear placement\n- Random scatter",
        feature_type="placement patterns"
    )
    print(post[:200] + "...")
    print()
    
    # Demo 3: Get recommendations
    print("🎯 DEMO 3: Get Posting Recommendations")
    print("-" * 70)
    recommendations = bot.get_next_post_recommendations()
    for i, rec in enumerate(recommendations[:3], 1):
        print(f"{i}. {rec['template']} - {rec['reason']}")
    print()
    
    # Demo 4: Analytics
    print("📊 DEMO 4: Analytics Overview")
    print("-" * 70)
    analytics = bot.monitor_engagement()
    print(f"Total Posts: {analytics['total_posts']}")
    print(f"Platforms: {len(analytics['posts_by_platform'])}")
    print()
    
    print("=" * 70)
    print("✅ Demo Complete!")
    print()
    print("Try it yourself:")
    print("  python forum_engagement_bot.py --action generate --template introduction")
    print("  python forum_engagement_bot.py --action recommend")
    print("=" * 70)

if __name__ == '__main__':
    main()
