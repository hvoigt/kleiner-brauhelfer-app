# iOS Build Instructions

This project includes a GitHub Actions workflow to build the iOS app without needing a Mac.

## Quick Start (Manual Trigger)

1. Push your code to GitHub
2. Go to your repository on GitHub
3. Click "Actions" tab
4. Select "Build iOS App" workflow
5. Click "Run workflow" button
6. Wait for the build to complete (10-15 minutes)
7. Download the IPA file from the workflow artifacts

## Setting Up Code Signing (Required for Device Installation)

To install the app on your iPhone, you need to configure code signing:

### 1. Get an Apple Developer Account
- Sign up at https://developer.apple.com ($99/year)
- Or use a free account (limited to 7 days per install)

### 2. Create Certificates and Provisioning Profile
Using a Mac (or MacinCloud):
1. Open Xcode
2. Go to Xcode → Preferences → Accounts
3. Add your Apple ID
4. Select your team and click "Manage Certificates"
5. Create an "iOS Development" certificate
6. Go to https://developer.apple.com/account
7. Create an App ID: `com.kleiner-brauhelfer.kleiner-brauhelfer-app`
8. Register your iPhone's UDID (find in Xcode or iTunes)
9. Create a Development Provisioning Profile

### 3. Export Certificate for GitHub Actions
On a Mac:
```bash
# Export certificate from Keychain Access
# File → Export Items → Save as .p12 file with password

# Convert to Base64 for GitHub Secret
base64 -i certificate.p12 | pbcopy
```

### 4. Add GitHub Secrets
In your GitHub repository:
1. Go to Settings → Secrets and variables → Actions
2. Add these secrets:
   - `APPLE_CERTIFICATE_BASE64`: The base64 encoded .p12 certificate
   - `APPLE_CERTIFICATE_PASSWORD`: Password for the .p12 file
   - `APPLE_TEAM_ID`: Your Team ID from developer.apple.com
   - `APPLE_PROVISIONING_PROFILE_BASE64`: Base64 encoded provisioning profile

## Installing IPA on Your iPhone

### Option 1: Using Xcode (Requires Mac)
1. Download IPA from GitHub Actions artifacts
2. Connect iPhone via USB
3. Open Xcode → Window → Devices and Simulators
4. Drag and drop the IPA onto your device

### Option 2: Using Diawi (Cloud Service)
1. Download IPA from GitHub Actions artifacts
2. Go to https://www.diawi.com
3. Upload the IPA file
4. Open the generated link on your iPhone
5. Install the app (must trust the certificate in Settings)

### Option 3: Using AltStore (No Mac Required)
1. Install AltStore on Windows/Linux: https://altstore.io
2. Download IPA from GitHub Actions artifacts
3. Use AltStore to sideload the IPA to your iPhone
4. Note: Apps expire after 7 days with free Apple account

### Option 4: Using iOS App Signer (Mac Required)
1. Download iOS App Signer: https://github.com/DanTheMan827/ios-app-signer
2. Sign the IPA with your certificate
3. Install via Xcode or Diawi

## Testing Without Code Signing

For initial testing to verify the build works:
1. The workflow will attempt to build even without secrets
2. The build may succeed but the IPA won't be installable
3. Check the build logs to ensure compilation succeeds
4. Once confirmed, set up code signing for actual device installation

## Troubleshooting

**Build fails with Qt installation error:**
- Check the Qt version in the workflow file matches available versions
- Try updating to latest Qt 6.x version

**Code signing errors:**
- Verify all secrets are correctly set in GitHub
- Ensure certificate and provisioning profile match
- Check that your device UDID is in the provisioning profile

**IPA won't install on device:**
- Verify the provisioning profile includes your device
- Check that the bundle identifier matches: `com.kleiner-brauhelfer.kleiner-brauhelfer-app`
- Ensure certificate is not expired

## Alternative: TestFlight Distribution

For easier distribution:
1. Build and archive the app through GitHub Actions
2. Upload to App Store Connect
3. Distribute via TestFlight (allows 10,000 testers)
4. Users install from TestFlight app on iPhone

This requires a paid Apple Developer account but is much simpler for ongoing testing.
