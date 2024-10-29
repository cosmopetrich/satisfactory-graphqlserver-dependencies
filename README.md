# satisfactory-graphqlserver-dependencies

This project contains the third-party C++ dependencies for [satisfactory-graphqlserver](https://github.com/cosmopetrich/satisfactory-graphqlserver).

It is used as a git submodule from that project, and artifacts which are too big for git are attached to its releases in a zipfile.

## License

The configuration of this repository itself is licensed under the GNU GPL 3.0.
However, the headers and binaries included in it are under the licenses of
[cppgraphqlgen](https://github.com/microsoft/cppgraphqlgen) (MIT), 
[uWebSockets](https://github.com/uNetworking/uWebSockets) (Apache 2.0), and their various dependencies.
These include Boost (BSL), PETGL (BSL), libuv (MIT), and zlib (zlib). See the .LICENSES directory.

## Building newer versions

Edit [vcpkg.json](vcpkg.json) and bump the `builtin-baseline` field to a newer commit ID on the [microsoft/vcpkg](https://github.com/microsoft/vcpkg) repository.
If you have vcpkg installed locally then you can use the [x-update-baseline command](https://learn.microsoft.com/en-us/vcpkg/commands/update-baseline) to do it for you.

Commit and push. Github Actions will build PRs which change the vcpkg config as a form of basic testing, and commits to master will automatically be turned into draft releases if the vcpkg config has changed. Builds of commits that don't change that config can be built triggered from the Actions page.

When Actions is done, visit [the releases page](https://github.com/cosmopetrich/satisfactory-graphqlserver-dependencies/releases) to promote draft PRs to real ones or delete unnecessary drafts
Once the release has been published you should update the submodule in the main repository.

```bash
cd Source/ThirdParty/GQLServerDeps
git pull
cd -
git commit Source/ThirdParty/GQLServerDeps -m "Bump ThirdParty"
git push
```

## Misc notes

Use of the static Windows build target is due to the fact that [it makes things slightly easier](https://docs.ficsit.app/satisfactory-modding/latest/Development/Cpp/thirdparty.html),
since I'm not sure if there's much benefit to using DLLs when we need to ship our own copy of them with the mod anyway, and since it gives us easy access to a static `schemagen.exe`.
Though note that [this StackOverflow question](https://stackoverflow.com/questions/140061/when-to-use-dynamic-vs-static-libraries) contains some back and forth on whether the runtime linker for DLLs might be more memory-efficient.

The header files are the ones generated by vcpkg's Windows target. The differences between these and those produced by the Linux target appear to be:
 - Line endings.
 - In zlib, `Z_HAVE_UNISTD_H` is enabled on Linux but not on Windows.

While the headers are checked in to git, the libs are far too large: a couple of hundred MB in total. Github-hosted LFS isn't a great solution as even a couple of users cloning the repository will quickly eat throught the monthly transfer quota. Instead, these larger files are zipped and attached to the project's Github release. The logic used to obtain these files should be something like the following.

 1. If `{debug,lib,tools}` doesn't exist, the release artifact is needed.
 2. If `cat .VERSION` doesn't match `cat lib/.VERSION`, the release artifact is needed.
 3. Remove `{debug,lib,tools}` if it exists.
 4. Download the artifact from the most recent non-draft release.
 5. Extract it to `Source/ThirdParty/GQLServerDeps` so that `Source/ThirdParty/GQLServerDeps/{debug,lib,tools}/` exist.
