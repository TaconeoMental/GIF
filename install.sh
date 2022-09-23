NAME=gif
DIR=$(pwd)
echo "#!/usr/bin/env sh
$DIR/gif" '"$@"' > $HOME/.local/bin/$NAME
chmod u+x $HOME/.local/bin/$NAME
