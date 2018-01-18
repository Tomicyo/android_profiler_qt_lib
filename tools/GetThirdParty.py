from CI.Download import download_and_extract
import argparse, sys

parser = argparse.ArgumentParser(description='Parse Dependency Options')

if len(sys.argv) < 2:
    print 'options needed'
    sys.exit(1)

parser.add_argument('--output_dir', help='specify output file path')
parser.add_argument('--target_os', help='available os are \'Windows\',\'WindowsUWP\',\'Android\',\'MacOS\'')
parser.add_argument('--ssl', help='whether download ssl prebuilt, default is no')

args = parser.parse_args(sys.argv[1:])

third_party_urls = {
    'Windows': 'https://ci.appveyor.com/api/projects/tomicyo/third-party/artifacts/artifacts/third_party_windows.zip',
    'Android': 'https://ci.appveyor.com/api/projects/tomicyo/third-party/artifacts/artifacts/third_party_android_arm64-v8a_gnustl_shared.zip'
}

openssl_urls = {
    'Windows': 'https://ci.appveyor.com/api/projects/tomicyo/openssl-ci/artifacts/artifacts/openssl_windows_md_shared.zip'
}

download_and_extract(third_party_urls[args.target_os], args.output_dir)

if '1' == args.ssl:
    download_and_extract(openssl_urls[args.target_os], args.output_dir)
