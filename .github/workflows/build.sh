#!/bin/bash
set -euxo pipefail

# derive the version from the git tag or commit id.
if [[ "${GITHUB_REF_TYPE}" == "tag" ]]; then
    VERSION="$(echo "${GITHUB_REF_NAME}" | sed 's/^v//')"
else
    VERSION="0.0.0-${GITHUB_SHA:0:7}"
fi

# set the version info file and product version.
RC_VERSION="$(echo -n "$VERSION" | perl -pe '
    s/^(\d+(?:\.\d+){1,3}).*/$1/;
    s/\./,/g;
    my @parts = split /,/;
    while (@parts < 4) { push @parts, 0; }
    $_ = join ",", @parts;
')"
perl -pi -e "s/^((FILEVERSION|PRODUCTVERSION)\s+).+/\${1}$RC_VERSION/" main.rc
perl -pi -e "s/^(\s+VALUE\s+\"(FileVersion|ProductVersion)\",\s+).+/\${1}\"$VERSION\"/" main.rc

# set the version info file flags.
if [[ "$VERSION" == *"-"* ]]; then
    RC_FLAGS='VS_FF_PRERELEASE'
else
    RC_FLAGS='0L'
fi
perl -pi -e "s/^((FILEFLAGS)\s+).+/\${1}$RC_FLAGS/" main.rc

make build run
