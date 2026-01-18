# Quick Start: Build iOS App Without a Mac

## Step 1: Push to GitHub

```bash
git add .
git commit -m "Add iOS build support"
git push origin master
```

## Step 2: Run the Workflow

1. Go to your GitHub repository
2. Click the **Actions** tab
3. Select **Build iOS App** workflow
4. Click **Run workflow** → **Run workflow**

The build will take 10-15 minutes.

## Step 3: Download the IPA

1. Wait for the workflow to complete (green checkmark)
2. Click on the workflow run
3. Scroll down to **Artifacts**
4. Download **kleiner-brauhelfer-app-ios.zip**
5. Extract to get **kleiner-brauhelfer-app.ipa**

## Step 4: Install on Your iPhone

### Without Code Signing (Initial Test)
The IPA built without secrets won't install on your device, but confirms the build works.

### With Code Signing (Actual Installation)

You have two main options:

#### Option A: Free Apple Account + AltStore (Easiest, No Mac)
1. Install AltStore on your computer: https://altstore.io
2. Connect your iPhone via USB
3. Add your free Apple ID to AltStore
4. Drag the IPA into AltStore to install
5. **Note**: Apps expire after 7 days and need reinstalling

#### Option B: Paid Apple Developer Account ($99/year)
1. Sign up at https://developer.apple.com
2. Use a cloud Mac service (MacinCloud, AWS EC2 Mac) or borrow a Mac
3. Generate certificates and provisioning profiles
4. Add secrets to GitHub (see `.github/workflows/IOS_BUILD_INSTRUCTIONS.md`)
5. Re-run workflow
6. Install IPA using Diawi.com or Xcode

## Recommended Path

**For quick testing:**
- Use **AltStore** with a free Apple account
- Simplest way to get the app on your phone
- No Mac needed
- Reinstall weekly

**For long-term use:**
- Get a paid Apple Developer account
- Set up proper code signing in GitHub
- Apps won't expire
- Can distribute to other testers

## Troubleshooting

**Workflow fails to build:**
- Check the Actions logs for errors
- Qt version might need updating in `ios-build.yml`

**Can't install IPA:**
- You need code signing (see options above)
- Unsigned IPAs from the workflow won't install

**Need help with code signing:**
- See detailed guide: `.github/workflows/IOS_BUILD_INSTRUCTIONS.md`
- Consider using AltStore for simpler setup

## What Was Changed

The following files enable iOS compilation:
- `kleiner-brauhelfer-app/CMakeLists.txt` - Added iOS build configuration
- `.github/workflows/ios-build.yml` - GitHub Actions workflow
- `.github/workflows/IOS_BUILD_INSTRUCTIONS.md` - Detailed instructions

The Android build is unchanged and still works normally.
