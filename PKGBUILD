# Maintainer: Raul Taranu <marvolo@taranusaur.us>
pkgname=dwm
pkgver=6.2
pkgrel=1
pkgdesc="A dynamic window manager for X"
arch=('i686' 'x86_64')
url="https://dwm.suckless.org/"
license=('MIT')
depends=()
makedepends=()
checkdepends=()
optdepends=()
conflicts=()
_patches=("https://dwm.suckless.org/patches/fullgaps/dwm-fullgaps-6.2.diff"
          "https://dwm.suckless.org/patches/barpadding/dwm-barpadding-6.2.diff"
          "https://dwm.suckless.org/patches/pertag/dwm-pertag-6.2.diff"
          "https://dwm.suckless.org/patches/rotatestack/dwm-rotatestack-20161021-ab9571b.diff"
          "https://dwm.suckless.org/patches/save_floats/dwm-savefloats-20181212-b69c870.diff"
          "https://dwm.suckless.org/patches/scratchpad/dwm-scratchpad-6.2.diff"
          "https://dwm.suckless.org/patches/monoclesymbol/dwm-monoclesymbol-6.2.diff"
          "https://dwm.suckless.org/patches/push/dwm-push_no_master-6.2.diff"
          # "https://dwm.suckless.org/patches/fibonacci/dwm-fibonacci-6.2.diff"
          #"https://dwm.suckless.org/patches/bottomstack/dwm-bottomstack-6.1.diff")
          "https://dwm.suckless.org/patches/centeredmaster/dwm-centeredmaster-20160719-56a31dc.diff")
source=("https://dl.suckless.org/dwm/$pkgname-$pkgver.tar.gz"
        "${_patches[@]}")
sha256sums=('97902e2e007aaeaa3c6e3bed1f81785b817b7413947f1db1d3b62b8da4cd110e'
            '3c59104f4b23b8ec3c31ff639712dc1214bd5e3a487f7af039268373eb9e0b2d'
            '199418d107838d53f058039bce433d858091670f88f7533c4107c129824d36ad'
            '055da0f12dbfde9e50df54e1f2d87966466404a36c056efb94bb21ab03b94b10'
            '27c889d424e1b539cd8b113d0c4f9693be521a0a2ef5adf246ecf3efb4208f3c'
            '88a08be82939fc57ab1c999a701a53e97644a02a8e7f269f986a507b8c62e340'
            'ffb89eb41d7a5e72471dcf92aed4a1b5dec207e65f23497d0522f15e99ebc29d'
            'ba8f4fcbf78c9c0f8b0c1dca27239e13a2b5ba4006589290cc3c373d5c3509d1'
            '1398b82ebb891e5c47a91a023be66d08c92d1355fe5a6614bda570fea6b46e4f'
            '0193d8be60cd3f978d1ee6876c39a2bbc154fbb95261e3680dc623317d905859')
_sourcedir=$pkgname-$pkgver
_makeopts="--directory=$_sourcedir"

prepare() {
  # This package provides a mechanism to provide a custom config.h. Multiple
  # configuration states are determined by the presence of two files in
  # $BUILDDIR:
  #
  # config.h  config.def.h  state
  # ========  ============  =====
  # absent    absent        Initial state. The user receives a message on how
  #                         to configure this package.
  # absent    present       The user was previously made aware of the
  #                         configuration options and has not made any
  #                         configuration changes. The package is built using
  #                         default values.
  # present                 The user has supplied his or her configuration. The
  #                         file will be copied to $srcdir and used during
  #                         build.
  #
  # After this test, config.def.h is copied from $srcdir to $BUILDDIR to
  # provide an up to date template for the user.
  if [ -e "$BUILDDIR/config.h" ]
  then
    cp "$BUILDDIR/config.h" "$_sourcedir"
  elif [ ! -e "$BUILDDIR/config.def.h" ]
  then
    msg='This package can be configured in config.h. Copy the config.def.h '
    msg+='that was just placed into the package directory to config.h and '
    msg+='modify it to change the configuration. Or just leave it alone to '
    msg+='continue to use default values.'
    warning "$msg"
  fi
  cp "$_sourcedir/config.def.h" "$BUILDDIR"

  # Apply patches
  for patch in "${_patches[@]}"; do
    echo "Applying patch $(basename $patch)..."
    patch --directory="$_sourcedir" < "$srcdir/$(basename $patch)"
  done
}

build() {
  make $_makeopts X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  local installopts='--mode 0644 -D --target-directory'
  local shrdir="$pkgdir/usr/share"
  local licdir="$shrdir/licenses/$pkgname"
  local docdir="$shrdir/doc/$pkgname"
  make $_makeopts PREFIX=/usr DESTDIR="$pkgdir" install
  install $installopts "$licdir" "$_sourcedir/LICENSE"
  install $installopts "$docdir" "$_sourcedir/README"
  # install $installopts "$shrdir/$pkgname" "$_sourcedir/st.info"
}
